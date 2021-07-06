//
// Created by Martin on 06.07.2021.
//

#include "gdt.hpp"

static GDTBlock gdt_block = {0};

GDTBlock *GetGDTBlock()
{
  return &gdt_block;
}

GDTBlock *GDTInit()
{
  uint16_t gdt_total_size = GDT_NUM * sizeof(struct GDTEntry);

  GDTSetEntry(&gdt_block, 0, 0, 0, 0);
  GDTSetEntry(&gdt_block, 1, 0, GDT_ACCESS_PRESENT | GDT_DESCRIPTOR_TYPE | GDT_ACCESS_EXECUTABLE | GDT_ACCESS_RW, GDT_FLAG_LONG | GDT_FLAG_PAGE_GRANULARITY); // kernel code segment
  GDTSetEntry(&gdt_block, 2, 0, GDT_ACCESS_PRESENT | GDT_DESCRIPTOR_TYPE | GDT_ACCESS_RW, GDT_FLAG_PAGE_GRANULARITY); // kernel data segment
  GDTSetEntry(&gdt_block, 3, 0, GDT_ACCESS_PRESENT | GDT_ACCESS_DPL3 | GDT_DESCRIPTOR_TYPE | GDT_ACCESS_EXECUTABLE | GDT_ACCESS_RW, GDT_FLAG_LONG | GDT_FLAG_PAGE_GRANULARITY); // user code segment
  GDTSetEntry(&gdt_block, 4, 0, GDT_ACCESS_PRESENT | GDT_ACCESS_DPL3 | GDT_DESCRIPTOR_TYPE | GDT_ACCESS_RW, GDT_FLAG_PAGE_GRANULARITY); // user data segment

  gdt_block.descriptor.size = gdt_total_size - 1;
  gdt_block.descriptor.offset = gdt_block.gdt;

  return &gdt_block;
}

void GDTSetEntry(GDTBlock *_gdt_block, size_t index, uint16_t limit, uint8_t access, uint8_t flags)
{
  if (index >= GDT_NUM) return;

  _gdt_block->gdt[index].Limit0 = limit;
  _gdt_block->gdt[index].AccessByte = access;
  _gdt_block->gdt[index].Flags = flags;
}