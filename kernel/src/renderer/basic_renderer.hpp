//
// Created by Martin on 06.07.2021.
//

#ifndef MATESOS2_BASIC_RENDERER_HPP
#define MATESOS2_BASIC_RENDERER_HPP

#include "stddef.h"
#include "../stivale/stivale_main.hpp"
#include "renderer_modules.hpp"
#include "basic_renderer_color.hpp"
#include "stdarg.h"

namespace BasicRenderer
{
  bool InitBasicRenderer(Color _front=BR_WHITE, Color _back=__BACKGROUND_COLOR);
  void FramebufferPutPixel(uint16_t x, uint16_t y, uint32_t pix);
  void FramebufferPutPixel(uint16_t x, uint16_t y, Color color);
  void ClearScreen(Color color);
  void ClearScreen();
  void Scroll();

  void PutChar(char c);
  void Print(const char *string);
  void Printf(const char *format, ...);

  void SetCursor(uint16_t x, uint16_t y);
  bool SetFont(PSF1Header *_fontHeader, uint8_t *_charBuffer);
  bool SetFont(Module _fontModule);
  void SetFrontColor(Color color);
  void SetBackColor(Color color);

  Framebuffer *GetFramebuffer();

  // image extension
  void DrawTGA(Module image, uint16_t xoff, uint16_t yoff, bool center=false);
  void DrawBMP(Module image, uint16_t xoff, uint16_t yoff, bool center=false);
}

#endif //MATESOS2_BASIC_RENDERER_HPP
