//
// Created by Martin on 14.07.2021.
//

#ifndef MATESOS2_KEYBOARD_SCANCODES_HPP
#define MATESOS2_KEYBOARD_SCANCODES_HPP

#include "stdint.h"

#define LeftShift 0x2A
#define RightShift 0x36
#define Enter 0x1C
#define BackSpace 0x0E
#define Spacebar 0x39
#define Escape 0x01
#define CapsLock 0x3A

#define SPECIAL_PREFIX 0xE0
#define SPECIAL_INS 0x52
#define SPECIAL_HOME 0x47
#define SPECIAL_PGUP 0x49
#define SPECIAL_DEL 0x53
#define SPECIAL_END 0x4F
#define SPECIAL_PGDN 0x51

namespace QWERTYKeyboard
{
  extern const char ASCIITable[];
  char Translate(uint8_t scancode, bool uppercase);
}

#endif //MATESOS2_KEYBOARD_SCANCODES_HPP
