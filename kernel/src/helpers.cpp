//
// Created by Martin on 02.07.2021.
//

#include "helpers.hpp"

__attribute__((noreturn))
void halt()
{
  while (true) asm("hlt");
}
