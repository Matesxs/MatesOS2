//
// Created by Martin on 06.07.2021.
//

#include "basic_renderer.hpp"
#include "framebuffer.hpp"
#include "psf1_font.hpp"
#include "../stivale/stivale_tags_structure.hpp"
#include "../stivale/stivale_main.hpp"

namespace BasicRenderer
{
  static Framebuffer framebuffer;
  static PSF1Font *psf1Font = NULL;

  void InitBasicRenderer()
  {
    StivaleTags *tags = getTags();
    framebuffer = (Framebuffer){.base_address=(void*)tags->framebuffer->framebuffer_addr,
                                .width=tags->framebuffer->framebuffer_width,
                                .height=tags->framebuffer->framebuffer_height,
                                .pitch=tags->framebuffer->framebuffer_pitch,
                                .bpp=tags->framebuffer->framebuffer_bpp};
    psf1Font = stivale2_get_font(tags->modules);
  }
}