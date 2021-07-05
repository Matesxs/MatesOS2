//
// Created by Martin on 02.07.2021.
//

#include "setup.hpp"
#include "memory/memory.hpp"
#include "stivale/tm_print.hpp"

void setupMemory()
{
  memory::InitPageframe();
  tm_printf("Page frame initialized");
  tm_printf("Total memory:    %d\nFree memory:     %d\nUsed memory:     %d\nReserved memory: %d", memory::GetTotalMemory(), memory::GetFreeMemory(), memory::GetUsedMemory(), memory::GetReservedMemory());

  memory::InitPaging();
  tm_printf("Paging initialized");
}
