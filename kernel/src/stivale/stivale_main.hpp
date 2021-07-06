//
// Created by Martin on 02.07.2021.
//

#ifndef MATESOS2_STIVALE_MAIN_HPP
#define MATESOS2_STIVALE_MAIN_HPP

#include "stdint.h"
#include "stddef.h"
#include "stivale2.h"
#include "../renderer/framebuffer.hpp"
#include "../renderer/psf1_font.hpp"

void *stivale2_get_tag(stivale2_struct *stivale2_struct, uint64_t id);
void stivale2_get_module(stivale2_struct_tag_modules* stivale2_struct, const char *sign, stivale2_module *module);
void printBootloaderInfo(stivale2_struct *stivale2_struct);
PSF1Font *stivale2_get_font(stivale2_struct_tag_modules* stivale2_struct);

#endif //MATESOS2_STIVALE_MAIN_HPP
