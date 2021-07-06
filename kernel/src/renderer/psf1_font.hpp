//
// Created by Martin on 06.07.2021.
//

#ifndef MATESOS2_PSF1_FONT_HPP
#define MATESOS2_PSF1_FONT_HPP

#include "stdint.h"

#define PSF1_MAGIC0 0x36
#define PSF1_MAGIC1 0x04

struct PSF1Header
{
  uint8_t magic[2];
  uint8_t filemode; // 0 : 256 characters, no unicode_data, 1 : 512 characters, no unicode_data, 2 : 256 characters, with unicode_data, 3 : 512 characters, with unicode_data
  uint8_t fontHeight;
};

struct PSF1Font
{
  PSF1Header header;
  uint8_t charBuffer[256];
};

#endif //MATESOS2_PSF1_FONT_HPP
