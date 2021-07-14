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

int memcmp (const void* str1, const void* str2, size_t count)
{
  char *s1 = (char*)str1;
  char *s2 = (char*)str2;

  while (count-- > 0)
  {
    if (*s1++ != *s2++)
      return s1[-1] < s2[-1] ? -1 : 1;
  }

  return 0;
}

void *memmove(void *__restrict__ dest, const void *__restrict__ src, size_t n)
{
  char *csrc = (char *)src;
  char *cdest = (char *)dest;

  char *temp = new char[n];

  for (size_t i=0; i<n; i++)
    temp[i] = csrc[i];

  for (size_t i=0; i<n; i++)
    cdest[i] = temp[i];

  delete [] temp;
  return cdest;
}