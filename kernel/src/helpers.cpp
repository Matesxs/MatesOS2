//
// Created by Martin on 08.07.2021.
//

#include "helpers.hpp"

uint8_t checksum(const char *addr, size_t size) noexcept
{
  const char *end = addr + size;
  uint8_t sum = 0;
  while (addr < end)
  {
    sum += *addr;
    addr++;
  }
  return sum;
}
