//
// Created by Martin on 07.07.2021.
//

#include "basic_renderer_color.hpp"

namespace BasicRenderer
{
  Color __BACKGROUND_COLOR = {5, 0, 40};
  Color BR_WHITE = {255, 255, 255};
  Color BR_BLACK = {0, 0, 0};
  Color BR_GRAY = {200, 200, 200};
  Color BR_DARK_GRAY = {100, 100, 100};
  Color BR_RED = {255, 0, 0};
  Color BR_DARK_RED = {127, 0, 0};
  Color BR_GREEN = {0, 255, 0};
  Color BR_DARK_GREEN = {0, 127, 0};
  Color BR_BLUE = {0, 0, 255};
  Color BR_DARK_BLUE = {0, 0, 127};
  Color BR_CYAN = {0, 255, 255};
  Color BR_DARK_CYAN = {0, 127, 127};
  Color BR_YELLOW = {255, 255, 0};
  Color BR_DARK_YELLOW = {127, 127, 0};
  Color BR_PURPLE = {255, 0, 255};
  Color BR_DARK_PURPLE = {127, 0, 127};

  Color rgb(uint8_t r, uint8_t g, uint8_t b)
  {
    return (Color){r, g, b};
  }

  uint32_t fromColor(Color color)
  {
    return ((color.r & 0xff) << 16) + ((color.g & 0xff) << 8) + (color.b & 0xff);
  }

  Color fromPixel(uint32_t pixel)
  {
    return Color{.r=(uint8_t)((pixel & 0x00ff0000) >> 16), .g=(uint8_t)((pixel & 0x0000ff00) >> 8), .b=(uint8_t)(pixel & 0x000000ff)};
  }
}