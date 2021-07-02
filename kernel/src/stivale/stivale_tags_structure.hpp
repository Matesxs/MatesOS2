//
// Created by Martin on 02.07.2021.
//

#ifndef MATESOS2_STIVALE_TAGS_STRUCTURE_HPP
#define MATESOS2_STIVALE_TAGS_STRUCTURE_HPP

#include "stivale2.h"

struct StivaleTags
{
  stivale2_struct_tag_terminal *terminal_tag;
  stivale2_struct_tag_memmap *memory_tag;
  stivale2_struct_tag_framebuffer *framebuffer;
  stivale2_struct_tag_rsdp *rsdp;
  stivale2_struct_tag_modules *modules;
};

StivaleTags *getTags();
StivaleTags *getTags(stivale2_struct *stivale2_struct);

#endif //MATESOS2_STIVALE_TAGS_STRUCTURE_HPP
