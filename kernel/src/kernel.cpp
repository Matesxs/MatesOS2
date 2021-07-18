//
// Created by Martin on 02.07.2021.
//

#include "stivale/stivale_main.hpp"
#include "setup.hpp"

#include "memory/memory.hpp"
#include "logging.hpp"
#include "renderer/basic_renderer.hpp"
#include "lib/stmm.hpp"

extern "C" __attribute__((unused, noreturn)) void _start(stivale2_struct *stivale2_struct)
{
  preSetup(stivale2_struct);
  setupMain();
  postSetup();

  asm("sti");

  BasicRenderer::Printf("\nAllocation of size 128\n");
  void *test = memory::calloc(128);
  memory::WalkHeap();

  BasicRenderer::Printf("\nRealloc to size 2048\n");
  void *tmpTest = memory::realloc(test, 2048);
  if (tmpTest != NULL) test = tmpTest;
  memory::WalkHeap();

  BasicRenderer::Printf("\nClean\n");
  memory::free(test);
  memory::WalkHeap();

  while(true) asm("hlt");
}