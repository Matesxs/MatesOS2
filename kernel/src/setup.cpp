//
// Created by Martin on 02.07.2021.
//

#include "setup.hpp"
#include "memory/memory.hpp"
#include "stivale/tm_print.hpp"
#include "stivale/stivale_tags_structure.hpp"
#include "renderer/basic_renderer.hpp"
#include "interrupts/interrupt.hpp"
#include "interrupts/interrupt_handlers.hpp"
#include "gdt/gdt.hpp"

void setupInterrupts()
{
  interrupts::Init();
  interrupts::AddHandler((void*)PageFault_Handler, 0xE, IDT_TA_InterruptGate, 0x08);
  interrupts::AddHandler((void*)DoubleFault_Handler, 0x8, IDT_TA_InterruptGate, 0x08);
  interrupts::AddHandler((void*)GPFault_Handler, 0xD, IDT_TA_InterruptGate, 0x08);
  interrupts::Load();
}

void setupMemory()
{
  Framebuffer fb = getTags()->framebuffer;
  size_t framebufferSize = fb.pitch * fb.height;

  memory::InitPageframe();
  memory::PageframeReserveSize((void*)fb.base_address, framebufferSize);

  memory::InitPaging();
  memory::IdentityMapSize((void*)fb.base_address, framebufferSize);
  memory::SetWritableSize((void*)fb.base_address, framebufferSize);
  memory::PageTable *l4_table = memory::GetL4Table();
  asm("mov %0, %%cr3" : : "r"(l4_table));
}

void preSetup()
{
  if (!BasicRenderer::InitBasicRenderer())
  {
    tm_printf("[PANIC] Failed to init basic renderer");
    while (true) asm("hlt");
  }
  BasicRenderer::ClearScreen();

  tm_disable(); // We can disable stivale terminal because now we have framebuffer
  GDTBlock *gtd_block = GDTInit();
  LoadGDT(&gtd_block->descriptor);

  setupInterrupts();
}
