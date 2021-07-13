//
// Created by Martin on 06.07.2021.
//

#ifndef MATESOS2_INTERRUPT_HANDLERS_HPP
#define MATESOS2_INTERRUPT_HANDLERS_HPP

#include "stdint.h"
#include "interrupt.hpp"

namespace interrupts
{
  __attribute__((interrupt, noreturn)) void PageFault_Handler(interrupt_frame *frame, uint64_t error_code);
  __attribute__((interrupt, noreturn)) void DoubleFault_Handler(interrupt_frame *frame, uint64_t error_code);
  __attribute__((interrupt, noreturn)) void GPFault_Handler(interrupt_frame *frame, uint64_t error_code);
  __attribute__((interrupt)) void KeyboardInt_Handler(interrupt_frame *frame);

  void InitExceptions();
}

#endif //MATESOS2_INTERRUPT_HANDLERS_HPP
