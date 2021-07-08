//
// Created by Martin on 06.07.2021.
//

#include "interrupt_handlers.hpp"
#include "../panic.hpp"
#include "interrupt.hpp"
#include "../logging.hpp"

namespace interrupts
{
  struct interrupt_frame;

  __attribute__((interrupt, noreturn)) static void PageFault_Handler(interrupt_frame *frame, uint64_t error_code)
  {
    Panic("Page Fault Detected");
    while (true) asm("hlt");
  }

  __attribute__((interrupt, noreturn)) static void DoubleFault_Handler(interrupt_frame *frame, uint64_t error_code)
  {
    Panic("Double Fault Detected");
    while (true) asm("hlt");
  }

  __attribute__((interrupt, noreturn)) static void GPFault_Handler(interrupt_frame *frame, uint64_t error_code)
  {
    Panic("General Protection Fault Detected");
    while (true) asm("hlt");
  }

  void InitExceptions()
  {
    AddHandler((void*)PageFault_Handler, 0xE, IDT_TA_TrapGate, 0x08);
    AddHandler((void*)DoubleFault_Handler, 0x8, IDT_TA_InterruptGate, 0x08);
    AddHandler((void*)GPFault_Handler, 0xD, IDT_TA_InterruptGate, 0x08);
    logging::log(logging::SUCCESS, "Exception handlers initialized");
  }
}
