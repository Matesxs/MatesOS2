//
// Created by Martin on 08.07.2021.
//

#ifndef MATESOS2_ACPI_HPP
#define MATESOS2_ACPI_HPP

#include "stdint.h"

namespace ACPI
{
  struct AddressStructure
  {
    uint8_t AddressSpace;
    uint8_t BitWidth;
    uint8_t BitOffset;
    uint8_t AccessSize;
    uint64_t Address;
  } __attribute__((packed));

  struct RSDP2
  {
    unsigned char Signature[8];
    uint8_t Checksum;
    uint8_t OEMId[6];
    uint8_t Revision;
    uint32_t RSDTAddress;
    uint32_t Length;
    uint64_t XSDTAddress;
    uint8_t ExtendedChecksum;
    uint8_t Reserved[3];
  } __attribute__((packed));

  struct SDTHeader
  {
    unsigned char Signature[4];
    uint32_t Length;
    uint8_t Revision;
    uint8_t Checksum;
    uint8_t OEMId[6];
    uint8_t OEMTableID[8];
    uint32_t OEMRevision;
    uint32_t CreatorID;
    uint32_t CreatorRevision;
  } __attribute__((packed));

  struct FACPHeader
  {
    SDTHeader SDT;
    uint32_t FIRMWARE_CTRL;
    uint32_t DSDT;
    uint8_t reserved1;
    uint8_t Preferred_PM_Profile;
    uint16_t SCI_INT;
    uint32_t SMI_CMD;
    uint8_t ACPI_ENABLE;
    uint8_t ACPI_DISABLE;
    uint8_t S4BIOS_REQ;
    uint8_t PSTATE_CNT;
    uint32_t PM1a_EVT_BLK;
    uint32_t PM1b_EVT_BLK;
    uint32_t PM1a_CNT_BLK;
    uint32_t PM1b_CNT_BLK;
    uint32_t PM2_CNT_BLK;
    uint32_t PM_TMR_BLK;
    uint32_t GPE0_BLK;
    uint32_t GPE1_BLK;
    uint8_t PM1_EVT_LEN;
    uint8_t PM1_CNT_LEN;
    uint8_t PM2_CNT_LEN;
    uint8_t PM_TMR_LEN;
    uint8_t GPE0_BLK_LEN;
    uint8_t GPE1_BLK_LEN;
    uint8_t GPE1_BASE;
    uint8_t CST_CNT;
    uint16_t P_LVL2_LAT;
    uint16_t P_LVL3_LAT;
    uint16_t FLUSH_SIZE;
    uint16_t FLUSH_STRIDE;
    uint8_t DUTY_OFFSET;
    uint8_t DUTY_WIDTH;
    uint8_t DAY_ALRM;
    uint8_t MON_ALRM;
    uint8_t CENTURY;
    uint16_t IAPC_BOOT_ARCH;
    uint8_t reserved2;
    uint32_t Flags;
    AddressStructure RESET_REG;
    uint8_t RESET_VALUE;
  } __attribute__((packed));

  void *FindXSDTTable(SDTHeader *sdtHeader, char *signature);
  int EnumXSDT(SDTHeader *sdtHeader);
  void* FindRSDTTable(SDTHeader *sdtHeader, char *signature);
  int EnumRSDT(SDTHeader *sdtHeader);
}

#endif //MATESOS2_ACPI_HPP
