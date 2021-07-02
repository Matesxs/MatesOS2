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