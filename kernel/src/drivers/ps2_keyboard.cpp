//
// Created by Martin on 14.07.2021.
//

#include "ps2_keyboard.hpp"
#include "../logging.hpp"
#include "../interrupts/interrupt.hpp"
#include "../interrupts/interrupt_handlers.hpp"
#include "../io/io.hpp"

const char driver_name[] = "ps2_keyboard";

namespace driver
{
  PS2KeyboardDriver::PS2KeyboardDriver()
  {
  }

  PS2KeyboardDriver::~PS2KeyboardDriver()
  {
  }

  bool PS2KeyboardDriver::activate()
  {
    asm("cli");

    interrupts::AddHandler((void*)interrupts::KeyboardInt_Handler, IRQ_PIC_OFFSET + IO_IRQ_KEYBOARD, IDT_TA_InterruptGate, 0x08);
    IO::io_pic_irq_enable(IO_IRQ_KEYBOARD);

    asm("sti");
    return true;
  }

  bool PS2KeyboardDriver::deactivate()
  {
    asm("cli");

    interrupts::RemoveHandler(IRQ_PIC_OFFSET + IO_IRQ_KEYBOARD);
    IO::io_pic_irq_disable(IO_IRQ_KEYBOARD);

    asm("sti");
    return true;
  }

  const char *PS2KeyboardDriver::getName()
  {
    return driver_name;
  }

  void PS2KeyboardDriver::handleScancode(uint8_t scancode)
  {
    logging::log(logging::INFO, "keybord interrupt handler called with scancode: %d", scancode);
  }
}