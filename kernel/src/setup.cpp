//
// Created by Martin on 02.07.2021.
//

#include "setup.hpp"
#include "lib/stmm.hpp"

void pre_setup()
{
  memset(&_WritableStart, 0, (uint64_t)&_WritableEnd - (uint64_t)&_WritableStart);
}
