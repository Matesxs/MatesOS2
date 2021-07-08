//
// Created by Martin on 02.07.2021.
//

#ifndef MATESOS2_STIVALE_TAGS_STRUCTURE_HPP
#define MATESOS2_STIVALE_TAGS_STRUCTURE_HPP

#include "stivale2.h"
#include "../renderer/framebuffer.hpp"
#include "module.hpp"

struct StivaleTags
{
  stivale2_struct_tag_terminal *terminal_tag;
  stivale2_struct_tag_memmap *memory_tag;
  Framebuffer framebuffer;
  stivale2_struct_tag_rsdp *rsdp;
  Module fontModule;
  Module bgImage;
};

StivaleTags *getTags();
StivaleTags *getTags(stivale2_struct *stivale2_struct);

#endif //MATESOS2_STIVALE_TAGS_STRUCTURE_HPP
