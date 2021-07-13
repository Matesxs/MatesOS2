//
// Created by Martin on 06.07.2021.
//

#ifndef MATESOS2_INTERRUPT_HPP
#define MATESOS2_INTERRUPT_HPP

#include "IDT.hpp"
#include "stdint.h"

namespace interrupts
{
  struct interrupt_frame;

  void Init();
  void AddHandler(void* handler, uint8_t entryOffset, uint8_t type_attr, uint8_t selector);
  void RemoveHandler(uint8_t entryOffset);
  void Load();
}

#endif //MATESOS2_INTERRUPT_HPP
