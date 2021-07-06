//
// Created by Martin on 06.07.2021.
//

#ifndef MATESOS2_IDT_HPP
#define MATESOS2_IDT_HPP

#include <stdint.h>

#define IDT_TA_InterruptGate 0b10001110
#define IDT_TA_CallGate      0b10001100
#define IDT_TA_TrapGate      0b10001111

struct IDTDescEntry
{
  uint16_t Offset0;
  uint16_t Selector;
  uint8_t Ist;
  uint8_t Type_Attr;
  uint16_t Offset1;
  uint32_t Offset2;
  uint32_t Zero;

  void SetOffset(uint64_t offset);
  uint64_t GetOffset();
};

struct IDTR
{
  uint16_t Limit;
  uint64_t Base;
}__attribute__((packed));

#endif //MATESOS2_IDT_HPP
