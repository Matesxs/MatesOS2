//
// Created by Martin on 06.07.2021.
//

#include "ststr.hpp"

int strcmp(const char *l, const char *r)
{
  for (; *l==*r && *l; l++, r++);
  return *(unsigned char *)l - *(unsigned char *)r;
}

int strcmp(const char *l, const char *r, size_t len)
{
  for (size_t i = 0; i < len && *l && *r; i++)
  {
    if (*l != *r) return *l - *r;
    l++; r++;
  }
  return 0;
}

size_t strlen(const char *s)
{
  size_t n = 0;
  while (*s)
  {
    n++;
    s++;
  }
  return n;
}