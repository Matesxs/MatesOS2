#pragma once

#include "stddef.h"
#include "stdint.h"
#include "../acpi.hpp"

namespace FACP
{
  void InitFACP(ACPI::FACPHeader *facp);
  void Shutdown();
  void Reboot();

  extern ACPI::FACPHeader *g_FACPHeader;
}