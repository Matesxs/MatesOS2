//
// Created by Martin on 02.07.2021.
//

#include "stivale/stivale_main.hpp"
#include "stivale/tm_print.hpp"

extern "C" __attribute__((unused, noreturn)) void _start(stivale2_struct *stivale2_struct)
{
  stivale2_struct_tag_terminal *term_str_tag = (stivale2_struct_tag_terminal *)stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_TERMINAL_ID);
  if (term_str_tag == NULL) while(true) asm("hlt");

  void *term_write_ptr = (void *)term_str_tag->term_write;
  stivale2_print = (void(*)(const char*, size_t))(term_write_ptr);

  tm_puts("Stivale2 info passed to the kernel:");
  tm_printf("Bootloader brand:   %s", stivale2_struct->bootloader_brand);
  tm_printf("Bootloader version: %s", stivale2_struct->bootloader_version);

  stivale2_tag *tag = (stivale2_tag *)stivale2_struct->tags;

  while (tag != NULL) {
    switch (tag->identifier) {
      case STIVALE2_STRUCT_TAG_MEMMAP_ID: {
        stivale2_struct_tag_memmap *m = (stivale2_struct_tag_memmap *)tag;
        tm_puts("Memmap tag:");
        tm_printf("\tEntries: %d", m->entries);
        for (size_t i = 0; i < m->entries; i++) {
          stivale2_mmap_entry me = m->memmap[i];
          tm_printf("\t\t[%x+%x] %x", me.base, me.length, me.type);
        }
        break;
      }

      case STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID: {
        stivale2_struct_tag_framebuffer *f = (stivale2_struct_tag_framebuffer *)tag;
        tm_puts("Framebuffer tag:");
        tm_printf("\tAddress: %x", f->framebuffer_addr);
        tm_printf("\tWidth:   %d", f->framebuffer_width);
        tm_printf("\tHeight:  %d", f->framebuffer_height);
        tm_printf("\tPitch:   %d", f->framebuffer_pitch);
        tm_printf("\tBPP:     %d", f->framebuffer_bpp);
        tm_printf("\tMemory model:    %d", f->memory_model);
        break;
      }

      case STIVALE2_STRUCT_TAG_TERMINAL_ID: {
        stivale2_struct_tag_terminal *term = (stivale2_struct_tag_terminal *)tag;
        tm_puts("Terminal tag:");
        tm_printf("\tTerminal write entry point at: %x", term->term_write);
        break;
      }

      case STIVALE2_STRUCT_TAG_MODULES_ID: {
        stivale2_struct_tag_modules *m = (stivale2_struct_tag_modules *)tag;
        tm_puts("Modules tag:");
        tm_printf("\tCount: %d", m->module_count);
        for (size_t i = 0; i < m->module_count; i++) {
          stivale2_module me = m->modules[i];
          tm_printf("\t\t[%x+%x] %s", me.begin, me.end, me.string);
        }
        break;
      }

      case STIVALE2_STRUCT_TAG_FIRMWARE_ID: {
        stivale2_struct_tag_firmware *f = (stivale2_struct_tag_firmware *)tag;
        tm_puts("Firmware tag:");
        tm_printf("\tFlags: %x", f->flags);
        break;
      }

      case STIVALE2_STRUCT_TAG_KERNEL_FILE_ID: {
        stivale2_struct_tag_kernel_file *t = (stivale2_struct_tag_kernel_file *)tag;
        tm_printf("Raw kernel file loaded at: %x", t->kernel_file);
        break;
      }

      default:
        break;
    }

    tag = (stivale2_tag *)tag->next;
  }

  while(true) asm("hlt");
}