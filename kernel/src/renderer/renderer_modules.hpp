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
}__attribute__((packed));

struct ModuleTGAHeader {
  uint8_t		id_length;
  uint8_t		color_map_type;
  uint8_t		image_type;
  uint16_t	color_map_index;
  uint16_t	color_map_length;
  uint8_t		depth;
  uint16_t	xorg;
  uint16_t	yorg;
  uint16_t	width;
  uint16_t	height;
  uint8_t		bbp;
  uint8_t		descriptor;
} __attribute__((packed));

#endif //MATESOS2_PSF1_FONT_HPP
