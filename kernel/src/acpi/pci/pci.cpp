#include "pci.hpp"
#include "../../panic.hpp"
#include "../../memory/memory.hpp"
#include "../../logging.hpp"
#include "../../lib/ststr.hpp"
#include "../../drivers/driver.hpp"
#include "../../drivers/ahci.hpp"

// #define DEBUG

#define MAX_NUMBER_OF_LANES 256

namespace PCI
{
  static struct PCIDeviceheader* s_pci_devices[MAX_NUMBER_OF_LANES];
  static size_t s_pci_devices_num = 0;

  void EnumerateFunction(uint64_t deviceAddress, uint64_t function)
  {
    uint64_t offset = function << 12;
    uint64_t functionAddress = deviceAddress + offset;

    memory::MemoryMap((void*)functionAddress, (void*)functionAddress);

    PCIDeviceheader *pciDeviceHeader = (PCIDeviceheader*)functionAddress;

    if (pciDeviceHeader->DeviceID == 0) return;
    if (pciDeviceHeader->DeviceID == 0xffff) return;

    if (s_pci_devices_num >= MAX_NUMBER_OF_LANES) return;
    s_pci_devices[s_pci_devices_num] = pciDeviceHeader;
    s_pci_devices_num++;
  }

  void EnumerateDevice(uint64_t busAddress, uint64_t device)
  {
    uint64_t offset = device << 15;
    uint64_t deviceAddress = busAddress + offset;

    memory::MemoryMap((void*)deviceAddress, (void*)deviceAddress);

    PCIDeviceheader *pciDeviceHeader = (PCIDeviceheader*)deviceAddress;

    if (pciDeviceHeader->DeviceID == 0) return;
    if (pciDeviceHeader->DeviceID == 0xffff) return;

    for (uint64_t function = 0; function < 8; function++)
    {
      EnumerateFunction(deviceAddress, function);
    }
  }

  void EnumerateBus(uint64_t baseAddress, uint64_t bus)
  {
    uint64_t offset = bus << 20;
    uint64_t busAddress = baseAddress + offset;

    memory::MemoryMap((void*)busAddress, (void*)busAddress);

    PCIDeviceheader *pciDeviceHeader = (PCIDeviceheader*)busAddress;

    if (pciDeviceHeader->DeviceID == 0) return;
    if (pciDeviceHeader->DeviceID == 0xffff) return;

    for (uint64_t device = 0; device < 32; device++)
    {
      EnumerateDevice(busAddress, device);
    }
  }

  void EnumeratePCI(ACPI::MCFGHeader *mcfg)
  {
    logging::log(logging::INFO, "PCI initializing");

    if (checksum((char*)&mcfg->Header, mcfg->Header.Length)) Panic("Failed SDT header checksum in MCFG header");
    if (mcfg->Header.Length < sizeof(ACPI::SDTHeader)) Panic("Impossible size of SDT header in MCFG header");

    uint64_t entries = ((mcfg->Header.Length) - sizeof(ACPI::MCFGHeader)) / sizeof(DeviceConfig);
    if (entries == 0)
    {
      logging::log(logging::WARNING, "No PCI buses found");
      return;
    }

    // PCIDeviceheader *device1 = EnumerateFunction(mcfg, 0, 0, 0, 0);
    // PCIDeviceheader *device2 = EnumerateFunction(mcfg, 0, 0, 0, 1);
    // PCIDeviceheader *device3 = EnumerateFunction(mcfg, 0, 0, 0, 2);
    // PCIDeviceheader *device4 = EnumerateFunction(mcfg, 0, 0, 0, 3);

    for (uint64_t t = 0; t < entries; t++)
    {
      DeviceConfig *newDeviceConfig = (DeviceConfig*)((uint64_t)mcfg + sizeof(ACPI::MCFGHeader) + (sizeof(DeviceConfig) * t));
      
      for (uint64_t bus = newDeviceConfig->StartBus; bus < newDeviceConfig->EndBus; bus++)
      {
        EnumerateBus(newDeviceConfig->BaseAddress, bus);
      }
    }

    for (size_t i = 0; i < s_pci_devices_num; i++)
    {
      PCIDeviceheader *pciDeviceHeader = s_pci_devices[i];

      logging::log(logging::INFOPlus, "%s / %s / %s / %s / %s",
                   GetVendorName(pciDeviceHeader->VendorID),
                   GetDeviceName(pciDeviceHeader->VendorID, pciDeviceHeader->DeviceID),
                   DeviceClasses[pciDeviceHeader->Class],
                   GetSubclassName(pciDeviceHeader->Class, pciDeviceHeader->Subclass),
                   GetProgramIFName(pciDeviceHeader->Class, pciDeviceHeader->Subclass, pciDeviceHeader->ProgIF));
      logging::newln();

      switch (pciDeviceHeader->Class)
      {
        case DC_MassStorageController:
          switch (pciDeviceHeader->Subclass)
          {
            case MSCSC_SATA: // Serial ATA
              switch (pciDeviceHeader->ProgIF)
              {
                case SATAPI_AHCI_1_0_Device: // AHCI 1.0 device
                  driver::g_DriverManager.add_driver(new AHCI::AHCIDriver(pciDeviceHeader));
                  break;
              }
              break;
          }
          break;

        case DC_SerialBusController:
          switch (pciDeviceHeader->Subclass)
          {
            case SBCSC_USBController:
              switch (pciDeviceHeader->ProgIF)
              {
                default:
                  break;
              }
              break;
          }
          break;
      }
    }

    logging::log(logging::SUCCESS, "PCI initialized");
  }

  PCIDeviceheader *EnumerateFunction(ACPI::MCFGHeader *mcfg, uint64_t entryIndex, uint64_t busIndex, uint64_t deviceIndex, uint64_t functionIndex)
  {
    uint64_t entries = ((mcfg->Header.Length) - sizeof(ACPI::MCFGHeader)) / sizeof(DeviceConfig);

    #ifdef DEBUG
      logging::log(logging::INFO, "Enumerating single PCI function");
      logging::log(logging::INFOPlus, "Bus entries: %d\n", entries);
    #endif

    if (entries <= entryIndex) return NULL;
    if (deviceIndex >= 32) return NULL;
    if (functionIndex >= 8) return NULL;

    DeviceConfig *newDeviceConfig = (DeviceConfig*)((uint64_t)mcfg + sizeof(ACPI::MCFGHeader) + (sizeof(DeviceConfig) * entryIndex));
    uint64_t bus = newDeviceConfig->StartBus + busIndex;

    #ifdef DEBUG
      logging::log(logging::INFOPlus, "Bus start: %d, Bus end: %d, Selected Bus: %d\n", newDeviceConfig->StartBus, newDeviceConfig->EndBus, bus);
    #endif

    if (bus >= newDeviceConfig->EndBus) return NULL;

    uint64_t offset1 = bus << 20;
    uint64_t busAddress = newDeviceConfig->BaseAddress + offset1;

    memory::IdentityMap((void*)busAddress);

    PCIDeviceheader *pciDevicesHeader = (PCIDeviceheader*)busAddress;

    #ifdef DEBUG
      logging::log(logging::INFOPlus, "L1 - Bus address: %x, DeviceID: %d, VendorID: %d\n", busAddress, pciDevicesHeader->DeviceID, pciDevicesHeader->VendorID);
    #endif

    if (pciDevicesHeader->DeviceID == 0) return NULL;
    if (pciDevicesHeader->DeviceID == 0xffff) return NULL;

    uint64_t offset2 = deviceIndex << 15;
    uint64_t deviceAddress = busAddress + offset2;

    memory::IdentityMap((void*)deviceAddress);

    PCIDeviceheader *pciDeviceHeader = (PCIDeviceheader*)deviceAddress;

    #ifdef DEBUG
      logging::log(logging::INFOPlus, "L2 - Device address: %x, DeviceID: %d, VendorID: %d\n", deviceAddress, pciDeviceHeader->DeviceID, pciDeviceHeader->VendorID);
    #endif

    if (pciDeviceHeader->DeviceID == 0) return NULL;
    if (pciDeviceHeader->DeviceID == 0xffff) return NULL;

    uint64_t offset3 = functionIndex << 12;
    uint64_t functionAddress = deviceAddress + offset3;

    memory::IdentityMap((void*)functionAddress);

    PCIDeviceheader *pciDeviceHeaderFunction = (PCIDeviceheader*)functionAddress;

    #ifdef DEBUG
    logging::log(logging::INFOPlus, "L3 - Function address: %x, DeviceID: %d, VendorID: %d\n", functionAddress, pciDeviceHeaderFunction->DeviceID, pciDeviceHeaderFunction->VendorID);
    #endif

    if (pciDeviceHeaderFunction->DeviceID == 0) return NULL;
    if (pciDeviceHeaderFunction->DeviceID == 0xffff) return NULL;

    return pciDeviceHeaderFunction;
  }
}