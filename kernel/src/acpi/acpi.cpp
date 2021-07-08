//
// Created by Martin on 08.07.2021.
//

#include "acpi.hpp"
#include "stddef.h"
#include "../lib/stmm.hpp"
#include "../lib/ststr.hpp"
#include "../logging.hpp"
#include "../panic.hpp"
#include "../helpers.hpp"

namespace ACPI
{
  void* FindXSDTTable(SDTHeader *sdtHeader, char *signature)
  {
    int entries = (sdtHeader->Length - sizeof(ACPI::SDTHeader)) / 8;
    for (int t = 0; t < entries; t++)
    {
      ACPI::SDTHeader *newSDTHeader = (ACPI::SDTHeader*)*(uint64_t*)((uint64_t)sdtHeader + sizeof(ACPI::SDTHeader) + (t * sizeof(uint64_t)));

      if (strcmp(signature, (char*)newSDTHeader->Signature, 4) != 0) continue;
      return newSDTHeader;
    }

    return NULL;
  }

  int EnumXSDT(SDTHeader *sdtHeader)
  {
    logging::log(logging::INFO,"Enumerating XSDT");

    if (checksum((char*)sdtHeader, sdtHeader->Length) != 0) Panic("Failed SDT header checksum (XSDT)");
    if (sdtHeader->Length < sizeof(SDTHeader)) Panic("Impossible size of SDT header (XSDT)");

    int entries = (sdtHeader->Length - sizeof(ACPI::SDTHeader)) / 8;
    if (entries > 0)
    {
      for (int t = 0; t < entries; t++)
      {
        ACPI::SDTHeader *newSDTHeader = (ACPI::SDTHeader*)*(uint64_t*)((uint64_t)sdtHeader + sizeof(ACPI::SDTHeader) + (t * sizeof(uint64_t)));

        if (checksum((char*)newSDTHeader, newSDTHeader->Length) != 0) Panic("Failed SDT header checksum");
        if (newSDTHeader->Length < sizeof(SDTHeader)) Panic("Impossible size of SDT header");

        char headerSignature[5];
        memcpy(headerSignature, newSDTHeader->Signature, 4);
        headerSignature[4] = '\0';

        logging::log(logging::INFOPlus, "%s / Revision: %d / OEM Revision %d / Creator Revision: %d", headerSignature, newSDTHeader->Revision, newSDTHeader->OEMRevision, newSDTHeader->CreatorRevision);
        logging::newln();
      }
    }

    return entries;
  }

  void* FindRSDTTable(SDTHeader *sdtHeader, char *signature)
  {
    int entries = (sdtHeader->Length - sizeof(ACPI::SDTHeader)) / sizeof(uint32_t);
    for (int t = 0; t < entries; t++)
    {
      ACPI::SDTHeader *newSDTHeader = (ACPI::SDTHeader*)*(uint32_t*)((uint64_t)sdtHeader + sizeof(ACPI::SDTHeader) + (t * sizeof(uint32_t)));

      if (strcmp(signature, (char*)newSDTHeader->Signature, 4) != 0) continue;
      return newSDTHeader;
    }

    return NULL;
  }

  int EnumRSDT(SDTHeader *sdtHeader)
  {
    logging::log(logging::INFO,"Enumerating RSDT");

    if (checksum((char*)sdtHeader, sdtHeader->Length) != 0) Panic("Failed SDT header checksum (RSDT)");
    if (sdtHeader->Length < sizeof(SDTHeader)) Panic("Impossible size of SDT header (RSDT)");

    int entries = (sdtHeader->Length - sizeof(ACPI::SDTHeader)) / sizeof(uint32_t);
    if (entries > 0)
    {
      for (int t = 0; t < entries; t++)
      {
        ACPI::SDTHeader *newSDTHeader = (ACPI::SDTHeader*)*(uint32_t*)((uint64_t)sdtHeader + sizeof(ACPI::SDTHeader) + (t * sizeof(uint32_t)));

        if (checksum((char*)newSDTHeader, newSDTHeader->Length) != 0) Panic("Failed SDT header checksum");
        if (newSDTHeader->Length < sizeof(SDTHeader)) Panic("Impossible size of SDT header");

        char headerSignature[5];
        memcpy(headerSignature, newSDTHeader->Signature, 4);
        headerSignature[4] = '\0';

        logging::log(logging::INFOPlus, "%s / Revision: %d / OEM Revision %d / Creator Revision: %d", headerSignature, newSDTHeader->Revision, newSDTHeader->OEMRevision, newSDTHeader->CreatorRevision);
        logging::newln();
      }
    }

    return entries;
  }
}
