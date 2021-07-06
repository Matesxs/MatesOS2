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
  stivale2_struct_tag_framebuffer *fb = getTags()->framebuffer;
  size_t framebufferSize = fb->framebuffer_pitch * fb->framebuffer_height;

  memory::InitPageframe();
  memory::PageframeReserveSize((void*)fb->framebuffer_addr, framebufferSize);

  memory::InitPaging();
  memory::IdentityMapSize((void*)fb->framebuffer_addr, framebufferSize);
  memory::SetWritableSize((void*)fb->framebuffer_addr, framebufferSize);
  memory::PageTable *l4_table = memory::GetL4Table();
  asm("mov %0, %%cr3" : : "r"(l4_table));
}

void preSetup()
{
  if (!BasicRenderer::InitBasicRenderer())
  {
    while (true) asm("hlt");
  }

  tm_disable();
  GDTBlock *gtd_block = GDTInit();
  LoadGDT(&gtd_block->descriptor);

  setupInterrupts();
}
