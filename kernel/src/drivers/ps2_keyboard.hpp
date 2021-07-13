//
// Created by Martin on 14.07.2021.
//

#ifndef MATESOS2_PS2_KEYBOARD_HPP
#define MATESOS2_PS2_KEYBOARD_HPP

#include "stdint.h"
#include "driver.hpp"

namespace driver
{
  class PS2KeyboardDriver : public Driver
  {
  public:
    PS2KeyboardDriver();
    ~PS2KeyboardDriver();
    virtual bool activate();
    virtual bool deactivate();
    virtual const char *getName();

    void handleScancode(uint8_t scancode);
  };
}

#endif //MATESOS2_PS2_KEYBOARD_HPP
