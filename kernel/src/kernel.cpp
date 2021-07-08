//
// Created by Martin on 02.07.2021.
//

#include "stivale/stivale_main.hpp"
#include "setup.hpp"

extern "C" __attribute__((unused, noreturn)) void _start(stivale2_struct *stivale2_struct)
{
  preSetup(stivale2_struct);
  setupMain();
  postSetup();

  asm("sti");

  while(true) asm("hlt");
}