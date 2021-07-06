//
// Created by Martin on 06.07.2021.
//

#ifndef MATESOS2_FRAMEBUFFER_HPP
#define MATESOS2_FRAMEBUFFER_HPP

#include "stdint.h"

struct Framebuffer
{
  void *base_address;
  uint16_t width;
  uint16_t height;
  uint16_t pitch; // Bytes in row
  uint16_t bpp;   // bits per one pixel
};

#endif //MATESOS2_FRAMEBUFFER_HPP
