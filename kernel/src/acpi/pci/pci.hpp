#pragma once

#include "stdint.h"
#include "stdint.h"
#include "../acpi.hpp"
#include "pci_enum.hpp"

namespace PCI
{
  struct PCIDeviceheader
  {
    uint16_t VendorID;
    uint16_t DeviceID;
    uint16_t Command;
    uint16_t Status;
    uint8_t RevisionID;
    uint8_t ProgIF;
    uint8_t Subclass;
    uint8_t Class;
    uint8_t CacheLineSize;
    uint8_t LatencyTimer;
    uint8_t HeaderType;
    uint8_t BIST;
  };

  struct PCIHeader0
  {
    PCIDeviceheader Header;
    uint32_t BAR0;
    uint32_t BAR1;
    uint32_t BAR2;
    uint32_t BAR3;
    uint32_t BAR4;
    uint32_t BAR5;
    uint32_t CardbusCISPtr;
    uint16_t SubsystemVendorID;
    uint16_t SubsystemID;
    uint32_t ExpansionROMBaseAddr;
    uint8_t CapabilitiesPtr;
    uint8_t Rsv0;
    uint16_t Rsv1;
    uint32_t Rsv2;
    uint8_t InterruptLine;
    uint8_t InterruptPin;
    uint8_t MinGrant;
    uint8_t MaxLatency;
  };

  struct DeviceConfig
  {
    uint64_t BaseAddress;
    uint16_t PCISigGroup;
    uint8_t StartBus;
    uint8_t EndBus;
    uint32_t Reserved;
  } __attribute__((packed));

  struct PCIClassIdentifier {
    uint8_t		classID;
    const char*	name;
  };
  struct PCISublassIdentifier {
    uint8_t		classID;
    uint8_t		subclassID;
    const char*	name;
  };
  struct PCIProgrammingInterfaceIdentifier {
    uint8_t		classID;
    uint8_t		subclassID;
    uint8_t		program_ifID;
    const char*	name;
  };

  struct PCIVendorIdentifier {
    uint16_t	vendorID;
    const char*	name;
  };

  extern struct PCIClassIdentifier g_pci_classes[];
  extern struct PCISublassIdentifier g_pci_subclasses[];
  extern struct PCIProgrammingInterfaceIdentifier g_pci_progifs[];
  extern struct PCIVendorIdentifier g_pci_vendors[];

  void EnumeratePCI(ACPI::MCFGHeader *mcfg);
  PCIDeviceheader *EnumerateFunction(ACPI::MCFGHeader *mcfg, uint64_t entryIndex, uint64_t busIndex, uint64_t deviceIndex, uint64_t functionIndex);

  const char* GetClassString(PCIDeviceheader* pci_header);
  const char* GetSubclassString(PCIDeviceheader* pci_header);
  const char* GetProgIFString(PCIDeviceheader* pci_header);
  const char* GetVendorString(PCIDeviceheader* pci_header);
}