//
// Created by Martin on 05.07.2021.
//

#include "bitmap.hpp"
#include "../lib/stmm.hpp"

void Bitmap::BitmapInit(uint8_t *_buffer, size_t _size)
{
  buffer = _buffer;
  size = _size;
  memset(buffer, 0, size);
}

size_t Bitmap::GetRealSize()
{
  return size * BITMAP_SCALE;
}

size_t Bitmap::GetSize()
{
  return size;
}

uint8_t *Bitmap::GetBuffer()
{
  return buffer;
}

bool Bitmap::operator[](size_t index)
{
  return Get(index);
}

bool Bitmap::Get(size_t index)
{
  if (index > GetRealSize())
    return false;

  uint64_t byteIndex = index / BITMAP_SCALE;
  uint8_t bitIndex = index % BITMAP_SCALE;
  uint8_t bitIndexer = 0b10000000 >> bitIndex;

  if((buffer[byteIndex] & bitIndexer) != 0) return true;
  return false;
}

bool Bitmap::Set(size_t index, bool value)
{
  if (index > GetRealSize())
    return false;

  uint64_t byteIndex = index / BITMAP_SCALE;
  uint8_t bitIndex = index % BITMAP_SCALE;
  uint8_t bitIndexer = 0b10000000 >> bitIndex;

  if(value)
  {
    buffer[byteIndex] |= bitIndexer;
  }
  else
  {
    buffer[byteIndex] &= ~bitIndexer;
  }

  return true;
}
