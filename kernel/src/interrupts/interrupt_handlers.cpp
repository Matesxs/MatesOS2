//
// Created by Martin on 06.07.2021.
//

#include "interrupt_handlers.hpp"

__attribute__((interrupt, noreturn)) void PageFault_Handler(interrupt_frame *frame)
{
  while (true) asm("hlt");
}

__attribute__((interrupt, noreturn)) void DoubleFault_Handler(interrupt_frame *frame)
{
  while (true) asm("hlt");
}

__attribute__((interrupt, noreturn)) void GPFault_Handler(interrupt_frame *frame)
{
  while (true) asm("hlt");
}
