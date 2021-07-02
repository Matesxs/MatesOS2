//
// Created by Martin on 02.07.2021.
//

#include "stivale_tags_structure.hpp"
#include "stivale_main.hpp"

bool tagsInitialized = false;
static StivaleTags s_stivaleTags;
StivaleTags *getTags(stivale2_struct *stivale2_struct)
{
  if (!tagsInitialized)
  {
    s_stivaleTags.framebuffer = (stivale2_struct_tag_framebuffer*)stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);
    s_stivaleTags.rsdp = (stivale2_struct_tag_rsdp*)stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_RSDP_ID);
    s_stivaleTags.memory_tag = (stivale2_struct_tag_memmap*)stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_MEMMAP_ID);
    s_stivaleTags.modules = (stivale2_struct_tag_modules*)stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_MODULES_ID);
    s_stivaleTags.terminal_tag = (stivale2_struct_tag_terminal*)stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_TERMINAL_ID);
  }

  return &s_stivaleTags;
}

StivaleTags *getTags()
{
  return &s_stivaleTags;
}
