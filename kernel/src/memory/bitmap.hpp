//
// Created by Martin on 05.07.2021.
//

#ifndef MATESOS2_BITMAP_HPP
#define MATESOS2_BITMAP_HPP

#include "stddef.h"
#include "stdint.h"

#define BITMAP_SCALE sizeof(size_t)

class Bitmap
{
public:
  void BitmapInit(uint8_t *_buffer, size_t _size);
  bool operator[](size_t index);
  bool Set(size_t index, bool value);
  bool Get(size_t index);
  size_t GetRealSize();
  size_t GetSize();
  uint8_t *GetBuffer();

private:
  uint8_t *buffer;
  size_t size;
};

#endif //MATESOS2_BITMAP_HPP
