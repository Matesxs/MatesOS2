//
// Created by Martin on 06.07.2021.
//

#include "interrupt_handlers.hpp"
#include "../panic.hpp"
#include "../logging.hpp"
#include "../io/io.hpp"
#include "../drivers/driver.hpp"
#include "../drivers/ps2_keyboard.hpp"
#include "stddef.h"

namespace interrupts
{
  __attribute__((interrupt, noreturn)) void PageFault_Handler(interrupt_frame *frame, uint64_t error_code)
  {
    Panic("Page Fault Detected");
    while (true) asm("hlt");
  }

  __attribute__((interrupt, noreturn)) void DoubleFault_Handler(interrupt_frame *frame, uint64_t error_code)
  {
    Panic("Double Fault Detected");
    while (true) asm("hlt");
  }

  __attribute__((interrupt, noreturn)) void GPFault_Handler(interrupt_frame *frame, uint64_t error_code)
  {
    Panic("General Protection Fault Detected");
    while (true) asm("hlt");
  }

  __attribute__((interrupt)) void KeyboardInt_Handler(interrupt_frame *frame)
  {
    uint8_t scanCode = IO::inb(0x60);
    driver::PS2KeyboardDriver *keyboardDriver = (driver::PS2KeyboardDriver*)driver::g_DriverManager.get_by_name("ps2_keyboard");
    if (keyboardDriver != NULL)
    {
      keyboardDriver->handleScancode(scanCode);
    }

    IO::io_pic_end_master();
  }

  void InitExceptions()
  {
    AddHandler((void*)PageFault_Handler, 0xE, IDT_TA_TrapGate, 0x08);
    AddHandler((void*)DoubleFault_Handler, 0x8, IDT_TA_TrapGate, 0x08);
    AddHandler((void*)GPFault_Handler, 0xD, IDT_TA_TrapGate, 0x08);
    logging::log(logging::SUCCESS, "Exception handlers initialized");
  }
}
