#pragma once

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

  void EnumeratePCI(ACPI::MCFGHeader *mcfg);
  PCIDeviceheader *EnumerateFunction(ACPI::MCFGHeader *mcfg, uint64_t entryIndex, uint64_t busIndex, uint64_t deviceIndex, uint64_t functionIndex);

  extern const char *DeviceClasses[];
  const char *GetVendorName(uint16_t vendorID);
  const char *GetDeviceName(uint16_t vendorID, uint16_t deviceID);
  const char *GetSubclassName(uint8_t classCode, uint8_t subclassCode);
  const char *GetProgramIFName(uint8_t classCode, uint8_t subclassCode, uint8_t progIF);
}