//
// Created by Martin on 02.07.2021.
//

#include "setup.hpp"
#include "memory/memory.hpp"
#include "stivale/tm_print.hpp"
#include "stivale/stivale_tags_structure.hpp"

void setupMemory()
{
  stivale2_struct_tag_framebuffer *fb = getTags()->framebuffer;
  size_t framebufferSize = fb->framebuffer_pitch * fb->framebuffer_height;

  memory::InitPageframe();
  memory::PageframeReserveSize((void*)fb->framebuffer_addr, framebufferSize);
  tm_printf("Page frame initialized");
  tm_printf("Total memory:    %d\nFree memory:     %d\nUsed memory:     %d\nReserved memory: %d", memory::GetTotalMemory(), memory::GetFreeMemory(), memory::GetUsedMemory(), memory::GetReservedMemory());

  memory::InitPaging();
  memory::IdentityMapSize((void*)fb->framebuffer_addr, framebufferSize);
  memory::SetWritableSize((void*)fb->framebuffer_addr, framebufferSize);
  memory::PageTable *l4_table = memory::GetL4Table();
  asm("mov %0, %%cr3" : : "r"(l4_table));
  tm_printf("Paging initialized");
}
