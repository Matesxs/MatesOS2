//
// Created by Martin on 02.07.2021.
//

#include "stivale/stivale_main.hpp"
#include "stivale/stivale_tags_structure.hpp"
#include "stivale/tm_print.hpp"
#include "setup.hpp"
#include "lib/stmm.hpp"

extern "C" __attribute__((unused, noreturn)) void _start(stivale2_struct *stivale2_struct)
{
  // Clear writable part of kernel in case there is some garbage
  memset(&_WritableStart, 0, (uint64_t)&_WritableEnd - (uint64_t)&_WritableStart);

  // Init basic functionality from bootloader
  getTags(stivale2_struct);
  tm_init();
  printBootloaderInfo(stivale2_struct);

  preSetup();
  setupMain();
  postSetup();

  asm("sti");

  while(true) asm("hlt");
}