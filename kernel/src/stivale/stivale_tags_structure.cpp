//
// Created by Martin on 02.07.2021.
//

#include "stivale_tags_structure.hpp"
#include "stivale_main.hpp"
#include "../renderer/renderer_modules.hpp"

bool tagsInitialized = false;
static StivaleTags s_stivaleTags = {0};

StivaleTags *getTags(stivale2_struct *stivale2_struct) {
  if (!tagsInitialized) {
    s_stivaleTags.rsdp = (stivale2_struct_tag_rsdp *) stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_RSDP_ID);
    s_stivaleTags.memory_tag = (stivale2_struct_tag_memmap *) stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_MEMMAP_ID);
    s_stivaleTags.terminal_tag = (stivale2_struct_tag_terminal *) stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_TERMINAL_ID);

    stivale2_get_framebuffer(stivale2_struct, &s_stivaleTags.framebuffer);
    stivale2_struct_tag_modules *modules = (stivale2_struct_tag_modules*) stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_MODULES_ID);
    stivale2_get_module(modules, "font", &s_stivaleTags.fontModule, sizeof(PSF1Header));
    stivale2_get_module(modules, "bgi", &s_stivaleTags.bgImage, sizeof(ModuleBMPHeader));
  }

  return &s_stivaleTags;
}

StivaleTags *getTags() {
  return &s_stivaleTags;
}
