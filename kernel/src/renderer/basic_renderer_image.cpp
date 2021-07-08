//
// Created by Martin on 08.07.2021.
//

#include "basic_renderer.hpp"

namespace BasicRenderer
{
  void DrawTGA(Module image, uint16_t xoff, uint16_t yoff, bool center)
  {
    ModuleTGAHeader *imageheader = (ModuleTGAHeader*)image.header;
    if (imageheader->bpp != 32 || imageheader->descriptor != 40) return;

    uint32_t* image_ptr = (uint32_t*)image.body;
    uint16_t height = imageheader->height;
    uint16_t width = imageheader->width;

    int32_t _xoff = xoff;
    int32_t _yoff = yoff;

    if (center)
    {
      _xoff -= width / 2;
      _yoff -= height / 2;
    }

    for(uint16_t dy = 0; dy < height; dy++)
    {
      for (uint16_t dx = 0; dx < width; dx++)
      {
        uint32_t offset = dx + (height * dy);
        uint32_t color = *(image_ptr + offset);
        int32_t x = (int32_t)dx + _xoff;
        int32_t y = (int32_t)dy + _yoff;

        if (x >= 0 && y >= 0)
        {
          FramebufferPutPixel((uint16_t)x, (uint16_t)y, color);
        }
      }
    }
  }

  void DrawBMP(Module image, uint16_t xoff, uint16_t yoff, bool center)
  {
    ModuleBMPHeader *bitmapHeader = (ModuleBMPHeader*)image.header;
    ModuleBMPInfoHeader *infoHeader = (ModuleBMPInfoHeader*)image.body;
    if (infoHeader->headerSize != 40) return; // its not INFOHEADER
    void *image_ptr = (void*)((uint64_t)image.header + bitmapHeader->dataAddressOffset);
  }
}
