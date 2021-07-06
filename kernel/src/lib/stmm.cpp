//
// Created by Martin on 02.07.2021.
//

#include "stmm.hpp"

void memset(void *start, uint8_t value, uint64_t num)
{
  for (uint64_t i = 0; i < num; i++)
  {
    *(uint8_t *)((uint64_t)start + i) = value;
  }
}

void *memcpy(void *__restrict__ dest, const void *__restrict__ src, size_t n)
{
  char *csrc = (char *)src;
  char *cdest = (char *)dest;

  for (; n; n--) *cdest++ = *csrc++;
  return cdest;
}