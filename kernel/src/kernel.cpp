//
// Created by Martin on 02.07.2021.
//

#include "stivale/stivale_main.hpp"
#include "stivale/stivale_tags_structure.hpp"
#include "stivale/tm_print.hpp"
#include "setup.hpp"

extern "C" __attribute__((unused, noreturn)) void _start(stivale2_struct *stivale2_struct)
{
  pre_setup();

  getTags(stivale2_struct);
  tm_init();
  printBootloaderInfo(stivale2_struct);

  while(true) asm("hlt");
}