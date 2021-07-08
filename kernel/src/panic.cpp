//
// Created by Martin on 08.07.2021.
//

#include "panic.hpp"
#include "renderer/basic_renderer.hpp"

__attribute__((noreturn))void Panic(const char *message)
{
  asm("cli");

  BasicRenderer::SetBackColor(BasicRenderer::BR_RED);
  BasicRenderer::SetFrontColor(BasicRenderer::BR_BLACK);

  BasicRenderer::ClearScreen();
  BasicRenderer::SetCursor(10, 15);
  BasicRenderer::Print("KERNEL PANIC\n\n");
  BasicRenderer::Print(message);

  while (true) asm("hlt");
}