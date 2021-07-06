//
// Created by Martin on 02.07.2021.
//

#ifndef MATESOS2_STIVALE_MAIN_HPP
#define MATESOS2_STIVALE_MAIN_HPP

#include "stdint.h"
#include "stddef.h"
#include "stivale2.h"
#include "module.hpp"

void *stivale2_get_tag(stivale2_struct *stivale2_struct, uint64_t id);
void stivale2_get_module(stivale2_struct_tag_modules* stivale2_struct, const char *sign, Module *module, size_t headerSize);
void printBootloaderInfo(stivale2_struct *stivale2_struct);

#endif //MATESOS2_STIVALE_MAIN_HPP
