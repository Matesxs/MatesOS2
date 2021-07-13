//
// Created by Martin on 14.07.2021.
//

#include "ps2_keyboard.hpp"
#include "../../logging.hpp"
#include "../../interrupts/interrupt.hpp"
#include "../../interrupts/interrupt_handlers.hpp"
#include "../../io/io.hpp"
#include "keyboard_scancodes.hpp"

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

  bool isLeftShiftPressed = false;
  bool isRightShiftPressed = false;
  bool capslockActivated = false;
  bool specialSet = false;
  void PS2KeyboardDriver::handleScancode(uint8_t scancode)
  {
    logging::log(logging::INFO, "keybord interrupt handler called with scancode: %d", scancode);
    if (specialSet)
    {
      // logging::log(logging::INFO, "Specialset activated");

      switch (scancode) {
        case SPECIAL_INS:
          break;

        case SPECIAL_HOME:
          break;

        case SPECIAL_PGUP:
          break;

        case SPECIAL_DEL:
          break;

        case SPECIAL_END:
          break;

        case SPECIAL_PGDN:
          break;
      }

      specialSet = false;
      return;
    }

    switch (scancode)
    {
      case SPECIAL_PREFIX:
        specialSet = true;
        return;

      case LeftShift:
        isLeftShiftPressed = true;
        return;

      case LeftShift + 0x80:
        isLeftShiftPressed = false;
        return;

      case RightShift:
        isRightShiftPressed = true;
        return;

      case RightShift + 0x80:
        isRightShiftPressed = false;
        return;

      case CapsLock:
        capslockActivated = !capslockActivated;
        return;

      case Escape:
        // FACP::Shutdown();
        return;

      case Enter:
        // g_BasicRenderer.NewLine();
        return;

      case Spacebar:
        // g_BasicRenderer.PutChar(' ');
        return;

      case BackSpace:
        // g_BasicRenderer.ClearChar();
        return;
    }

    char ascii = QWERTYKeyboard::Translate(scancode, isLeftShiftPressed | isRightShiftPressed | capslockActivated);
    if (ascii != 0)
    {
      logging::log(logging::INFO, "Scancode translated to %c\n", ascii);
    }
  }
}