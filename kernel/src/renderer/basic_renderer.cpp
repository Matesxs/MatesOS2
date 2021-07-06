//
// Created by Martin on 06.07.2021.
//

#include "basic_renderer.hpp"
#include "framebuffer.hpp"
#include "renderer_modules.hpp"
#include "../stivale/stivale_tags_structure.hpp"
#include "../stivale/stivale_main.hpp"

namespace BasicRenderer
{
  static Framebuffer framebuffer;

  static PSF1Header *psf1FontHeader = NULL;
  static uint8_t *fontCharset = NULL;
  uint64_t numberOfChars = 0;

  bool InitBasicRenderer()
  {
    StivaleTags *tags = getTags();
    framebuffer = (Framebuffer){.base_address=(void*)tags->framebuffer->framebuffer_addr,
                                .width=tags->framebuffer->framebuffer_width,
                                .height=tags->framebuffer->framebuffer_height,
                                .pitch=tags->framebuffer->framebuffer_pitch,
                                .bpp=tags->framebuffer->framebuffer_bpp};

    if (framebuffer.base_address == NULL || framebuffer.width == 0 || framebuffer.height == 0)
      return false; // TODO: Return some error, invalid framebuffer received

    Module fontModule;
    stivale2_get_module(tags->modules, "font", &fontModule, sizeof(PSF1Header));
    if (fontModule.header == NULL || fontModule.body == NULL || fontModule.size <= sizeof(PSF1Header))
      return false; // TODO: Some error, modul is not valid

    psf1FontHeader = (PSF1Header*)fontModule.header;
    if (psf1FontHeader->magic[0] != PSF1_MAGIC0 || psf1FontHeader->magic[1] != PSF1_MAGIC1)
      return false; // TODO: Some error, font is corrupted

    if (psf1FontHeader->filemode == 0 || psf1FontHeader->filemode == 2)
      // 256 characters (ignoring unicode)
      numberOfChars = 256;
    else if (psf1FontHeader->filemode == 1 || psf1FontHeader->filemode == 3)
      // 512 characters (ignoring unicode)
      numberOfChars = 512;
    else
      // TODO: Return some error, garbage received
      return false;

    fontCharset = (uint8_t*)fontModule.body;
    return true;
  }
}