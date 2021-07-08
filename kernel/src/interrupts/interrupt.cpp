//
// Created by Martin on 06.07.2021.
//

#include "interrupt.hpp"
#include "stddef.h"

namespace interrupts
{
  static IDTR idtr = {0};
  static IDTDescEntry idt_entries[256];

  void Init()
  {
    idtr.Limit = sizeof(IDTDescEntry) * 256 - 1;
    idtr.Base = (uint64_t)&idt_entries;
  }

  void AddHandler(void* handler, uint8_t entryOffset, uint8_t type_attr, uint8_t selector)
  {
    IDTDescEntry *interrupt = (IDTDescEntry*)(idtr.Base + entryOffset * sizeof(IDTDescEntry));
    interrupt->SetOffset((uint64_t)handler);
    interrupt->Type_Attr = type_attr;
    interrupt->Selector = selector;
    interrupt->Zero = 0;
  }

  void RemoveHandler(uint8_t entryOffset)
  {
    IDTDescEntry *interrupt = (IDTDescEntry*)(idtr.Base + entryOffset * sizeof(IDTDescEntry));
    interrupt->SetOffset((uint64_t)NULL);
    interrupt->Type_Attr = 0;
    interrupt->Selector = 0;
    interrupt->Zero = 0;
  }

  void Load()
  {
    asm ("lidt %0" : : "m" (idtr));
  }
}
