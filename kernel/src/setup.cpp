//
// Created by Martin on 02.07.2021.
//

#include "setup.hpp"
#include "memory/memory.hpp"
#include "stivale/tm_print.hpp"
#include "stivale/stivale_tags_structure.hpp"
#include "renderer/basic_renderer.hpp"
#include "logging.hpp"
#include "interrupts/interrupt.hpp"
#include "interrupts/interrupt_handlers.hpp"
#include "gdt/gdt.hpp"

void setupInterrupts()
{
  interrupts::Init();
  interrupts::InitExceptions();
  interrupts::Load();

  logging::log(logging::SUCCESS, "Interrupts initialized");
}

void setupMemory()
{
  Framebuffer fb = getTags()->framebuffer;
  size_t framebufferSize = fb.pitch * fb.height;

  memory::InitPageframe();
  memory::PageframeReserveSize((void*)fb.base_address, framebufferSize);
  logging::log(logging::SUCCESS, "Pageframe loaded");

  memory::InitPaging();
  memory::IdentityMapSize((void*)fb.base_address, framebufferSize);
  memory::SetWritableSize((void*)fb.base_address, framebufferSize);
  memory::PageTable *l4_table = memory::GetL4Table();
  asm("mov %0, %%cr3" : : "r"(l4_table));

  logging::log(logging::SUCCESS, "Paging setup");
}

void preSetup()
{
  if (!BasicRenderer::InitBasicRenderer())
  {
    tm_printf("[PANIC] Failed to init basic renderer");
    while (true) asm("hlt");
  }
  BasicRenderer::ClearScreen();
  BasicRenderer::SetCursor(4, 0);

  logging::log(logging::SUCCESS, "Basic Renderer initialized");

  tm_disable(); // We can disable stivale terminal because now we have framebuffer
  GDTBlock *gtd_block = GDTInit();
  LoadGDT(&gtd_block->descriptor);
  logging::log(logging::SUCCESS, "GDT Loaded");

  setupInterrupts();
}
