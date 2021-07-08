//
// Created by Martin on 07.07.2021.
//

#ifndef MATESOS2_BASIC_RENDERER_COLOR_HPP
#define MATESOS2_BASIC_RENDERER_COLOR_HPP

#include "stdint.h"

namespace BasicRenderer
{
  struct Color
  {
    /** Red */
    uint8_t r;
    /** Green */
    uint8_t g;
    /** Blue */
    uint8_t b;
  };

  extern Color __BACKGROUND_COLOR;
  extern Color BR_WHITE;
  extern Color BR_BLACK;
  extern Color BR_GRAY;
  extern Color BR_DARK_GRAY;
  extern Color BR_RED;
  extern Color BR_DARK_RED;
  extern Color BR_GREEN;
  extern Color BR_DARK_GREEN;
  extern Color BR_BLUE;
  extern Color BR_DARK_BLUE;
  extern Color BR_CYAN;
  extern Color BR_DARK_CYAN;
  extern Color BR_YELLOW;
  extern Color BR_DARK_YELLOW;
  extern Color BR_PURPLE;
  extern Color BR_DARK_PURPLE;

  Color rgb(uint8_t r, uint8_t g, uint8_t b);
  uint32_t fromColor(Color color);
  Color fromPixel(uint32_t pixel);
}

#endif //MATESOS2_BASIC_RENDERER_COLOR_HPP
