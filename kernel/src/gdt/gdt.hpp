//
// Created by Martin on 06.07.2021.
//

#ifndef MATESOS2_GDT_HPP
#define MATESOS2_GDT_HPP

#include "stdint.h"
#include "stddef.h"

#define GDT_NUM 5

enum GDTAccess {
  GDT_ACCESS_RW = 0b00000010,
  GDT_DESCRIPTOR_TYPE = 0b00010000,
  GDT_ACCESS_PRESENT = 0b10000000,
  GDT_ACCESS_EXECUTABLE = 0b00001000,
  GDT_ACCESS_DPL3 = 0b01100000,
};

enum GDTFlags {
  GDT_FLAG_SIZE = 0b01000000,
  GDT_FLAG_LONG = 0b00100000,
  GDT_FLAG_PAGE_GRANULARITY = 0b10000000,
};

struct GDTEntry {
  uint16_t Limit0;
  uint16_t Base0;
  uint8_t Base1;
  uint8_t AccessByte;
  uint8_t Flags;
  uint8_t Base2;
}__attribute__((packed));

struct GDTDescriptor {
  uint16_t size;
  GDTEntry *offset;
} __attribute__((packed));

struct GDTBlock {
  GDTDescriptor descriptor;
  GDTEntry gdt[GDT_NUM];
};

GDTBlock *GDTInit();

void GDTSetEntry(GDTBlock *gdt_block, size_t index, uint16_t limit, uint8_t access, uint8_t flags);

GDTBlock *GetGDTBlock();

extern "C" void LoadGDT(GDTDescriptor *gdtDescriptor);

#endif //MATESOS2_GDT_HPP
