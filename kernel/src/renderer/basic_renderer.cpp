//
// Created by Martin on 06.07.2021.
//

#include "basic_renderer.hpp"
#include "../stivale/stivale_tags_structure.hpp"
#include "../helpers.hpp"

static const char CONVERSION_TABLE[] = "0123456789abcdef";

namespace BasicRenderer
{
  Framebuffer *framebuffer = NULL;
  PSF1Header *fontHeader = NULL;
  uint8_t *charBuffer = NULL;
  static uint64_t number_of_chars = 0;

  static uint16_t xGridMax = 0;
  static uint16_t yGridMax = 0;

  static uint16_t baseXPos = 0;
  static uint16_t cursorX = 0;
  static uint16_t cursorY = 0;

  static Color backColor;
  static Color frontColor;

  void FramebufferPutPixel(uint16_t x, uint16_t y, uint32_t pix)
  {
    if (x < framebuffer->width && y < framebuffer->height)
      ((uint32_t*)framebuffer->base_address)[y * framebuffer->width + x] = pix;
  }

  void FramebufferPutPixel(uint16_t x, uint16_t y, Color color)
  {
    FramebufferPutPixel(x, y, fromColor(color));
  }

  bool InitBasicRenderer(Color _front, Color _back)
  {
    StivaleTags *tags = getTags();
    Module fontModule = tags->fontModule;

    Framebuffer *tmpFramebuffer = &tags->framebuffer;
    if (tmpFramebuffer->base_address == NULL)
    {
      // TODO: Return framebuffer not found
      return false;
    }

    if (tmpFramebuffer->pitch == 0 || tmpFramebuffer->bpp == 0 || tmpFramebuffer->width == 0 || tmpFramebuffer->height == 0)
    {
      // TODO: Return invalid framebuffer
      return false;
    }

    framebuffer = tmpFramebuffer;
    backColor = _back;
    frontColor = _front;

    return SetFont(fontModule);
  }

  void ClearScreen(Color color)
  {
    if (framebuffer != NULL)
    {
      uint32_t clear_color = fromColor(color);

      for (uint16_t y = 0; y < framebuffer->height; y++)
      {
        for (uint16_t x = 0; x < framebuffer->width; x++)
        {
          FramebufferPutPixel(x, y, clear_color);
        }
      }
    }
  }

  void ClearScreen()
  {
    ClearScreen(backColor);
  }

  void Scroll()
  {
    if (framebuffer == NULL) return;

    size_t rowSize = framebuffer->pitch * fontHeader->fontHeight / sizeof(uint32_t);
    size_t screenSize = framebuffer->pitch * fontHeader->fontHeight * yGridMax / sizeof(uint32_t);

    size_t i = 0;
    for (; i < screenSize - rowSize; i++)
    {
      ((uint32_t*)framebuffer->base_address)[i] = ((uint32_t*)framebuffer->base_address)[i + rowSize];
    }

    for (size_t j = 0; j < rowSize; j++)
    {
      ((uint32_t*)framebuffer->base_address)[i + j] = fromColor(backColor);
    }
  }

  void PutChar(char c)
  {
    if (framebuffer == NULL || fontHeader == NULL) return;

    while (cursorY >= yGridMax)
    {
      if (cursorY == 0) break;
      cursorY--;
      Scroll();
    }

    uint16_t x_start_pix = cursorX * PSF1_CHAR_WIDTH;
    uint16_t y_start_pix = cursorY * fontHeader->fontHeight;

    char *fontPtr = (char *)charBuffer + (c * fontHeader->fontHeight);

    if (c == '\n')
    {
      goto newline;
    }
    else if (c == '\t')
    {
      Print("  ");
      return;
    }

    for (uint16_t y = y_start_pix; y < y_start_pix + fontHeader->fontHeight; y++)
    {
      for (uint16_t x = x_start_pix; x < x_start_pix + PSF1_CHAR_WIDTH; x++)
      {
        if ((*fontPtr & (0b10000000 >> (x - x_start_pix))) > 0)
          FramebufferPutPixel(x, y, frontColor);
        else
          FramebufferPutPixel(x, y, backColor);
      }

      fontPtr++;
    }

    cursorX += 1;
    if (cursorX + 1 > xGridMax)
    {
newline:
      cursorY += 1;
      cursorX = baseXPos;
    }

    while (cursorY >= yGridMax)
    {
      if (cursorY == 0) break;
      cursorY--;
      Scroll();
    }
  }

  void NewLine()
  {
    PutChar('\n');
  }

  void Print(const char *string)
  {
    while (*string != '\0')
    {
      PutChar(*string);
      string++;
    }
  }

  static void PrintHex(size_t num) {
    int i;
    char buf[17];

    if (!num) {
      Print("0x0");
      return;
    }

    buf[16] = 0;

    for (i = 15; num; i--) {
      buf[i] = CONVERSION_TABLE[num % 16];
      num /= 16;
    }

    i++;
    Print("0x");
    Print(&buf[i]);
  }

  static void PrintDec(size_t num) {
    int i;
    char buf[21] = {0};

    if (!num) {
      PutChar('0');
      return;
    }

    for (i = 19; num; i--) {
      buf[i] = (num % 10) + 0x30;
      num = num / 10;
    }

    i++;
    Print(buf + i);
  }

  static void PrintSize(size_t size)
  {
    if (size / 1099511627776 > 1)
    {
      PrintDec(size / 1099511627776);
      Print("TB");
    }
    else if (size / 1073741824 > 1)
    {
      PrintDec(size / 1073741824);
      Print("GB");
    }
    else if (size / 1048576 > 1)
    {
      PrintDec(size / 1048576);
      Print("MB");
    }
    else if (size / 1024 > 1)
    {
      PrintDec(size / 1024);
      Print("KB");
    }
    else
    {
      PrintDec(size);
      Print("B");
    }
  }

  void Printf(const char *format, ...)
  {
    va_list argp;
    va_start(argp, format);
    Printfa(format, argp);
    va_end(argp);
  }

  const char Digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
  const size_t DigitsSize = sizeof(Digits) - 1;
  char toString_convertOutput[128];
  const char* to_string_convert(uint64_t value, uint64_t base)
  {
    if (base < 2 || base > DigitsSize)
    {
      toString_convertOutput[0] = 0;
      return toString_convertOutput;
    }

    char buffer[128] = {};
    char* p = buffer + 128;

    int i = 0;
    while (value != 0)
    {
      *(--p) = Digits[value % base];
      value /= base;
      i++;
    }

    char *fb = toString_convertOutput;
    while (i)
    {
      *fb = *p;
      fb++;
      p++;
      i--;
    }

    return toString_convertOutput;
  }

  void Printfa(const char *format, va_list argp)
  {
    while (*format != '\0') {
      if (*format == '%') {
        format++;
        if (*format == 'x') {
          PrintHex(va_arg(argp, size_t));
        } else if (*format == 'd') {
          PrintDec(va_arg(argp, size_t));
        } else if (*format == 's') {
          Print(va_arg(argp, char*));
        } else if (*format == 'S') {
          PrintSize(va_arg(argp, size_t));
        } else if (*format == 'c') {
          PutChar((char)va_arg(argp, int));
        } else if (*format == 'b') {
          Print(to_string_convert(va_arg(argp, size_t), 2));
        }
      } else {
        PutChar(*format);
      }
      format++;
    }
  }

  void SetCursor(uint16_t x, uint16_t y)
  {
    if (framebuffer != NULL)
    {
      if (x < xGridMax)
      {
        cursorX = x;
      }
      else
      {
        cursorX = xGridMax - 1;
      }

      baseXPos = cursorX;

      if (y < yGridMax)
      {
        cursorY = y;
      }
      else
      {
        cursorY = yGridMax - 1;
      }
    }
  }

  bool SetFont(Module _fontModule)
  {
    if (_fontModule.header == NULL || _fontModule.body == NULL || _fontModule.size <= sizeof(PSF1Header))
    {
      // TODO: Return font module corrupted
      return false;
    }

    return SetFont((PSF1Header*)_fontModule.header, (uint8_t*)_fontModule.body);
  }

  bool SetFont(PSF1Header *_fontHeader, uint8_t *_charBuffer)
  {
    if (_fontHeader->magic[0] != PSF1_MAGIC0 || _fontHeader->magic[1] != PSF1_MAGIC1 || _fontHeader->filemode > 3)
    {
      // TODO: Return invalid font header
      return false;
    }

    if (_fontHeader->filemode == 0 || _fontHeader->filemode == 2)
      // 256 characters (ignoring unicode)
      number_of_chars = 256;
    else
      // 512 characters (ignoring unicode)
      number_of_chars = 512;

    fontHeader = _fontHeader;
    charBuffer = _charBuffer;

    if (framebuffer != NULL)
    {
      xGridMax = framebuffer->width / PSF1_CHAR_WIDTH;
      yGridMax = framebuffer->height / fontHeader->fontHeight;

      if (cursorX >= xGridMax) cursorX = xGridMax - 1;
      if (cursorY >= yGridMax) cursorY = yGridMax - 1;
    }

    return true;
  }

  void SetFrontColor(Color color)
  {
    frontColor = color;
  }

  void SetBackColor(Color color)
  {
    backColor = color;
  }

  Color GetFrontColor()
  {
    return frontColor;
  }

  Framebuffer *GetFramebuffer()
  {
    return framebuffer;
  }
}