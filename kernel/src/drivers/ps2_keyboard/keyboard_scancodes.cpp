//
// Created by Martin on 14.07.2021.
//

#include "keyboard_scancodes.hpp"

namespace QWERTYKeyboard
{
  const char ASCIITable[] = {
      0, 0, '1', '2',
      '3', '4', '5', '6',
      '7', '8', '9', '0',
      '-', '=', 0, 0,
      'q', 'w', 'e', 'r',
      't', 'y', 'u', 'i',
      'o', 'p', '[', ']',
      0, 0, 'a', 's',
      'd', 'f', 'g', 'h',
      'j', 'k', 'l', ';',
      '\'', '`', 0, '\\',
      'z', 'x', 'c', 'v',
      'b', 'n', 'm', ',',
      '.', '/', 0, '*',
      0, ' '};

  char Translate(uint8_t scancode, bool uppercase)
  {
    if (scancode > 58) return 0;

    char retChar = ASCIITable[scancode];

    if (uppercase)
    {
      if (retChar >= 'a' && retChar <= 'z')
      {
        retChar -= 32;
      }
      else if (retChar >= '0' && retChar <= '9')
      {
        retChar -= 16;
      }
    }

    return retChar;
  }
}
