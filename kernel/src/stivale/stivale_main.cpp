//
// Created by Martin on 02.07.2021.
//

#include "stivale_main.hpp"
#include "tm_print.hpp"
#include "../lib/ststr.hpp"
#include "../lib/stmm.hpp"

// TODO: Set this according to definition of page size
static uint8_t stack[4096 * 32];

struct stivale2_header_tag_smp smp_request = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_SMP_ID,
        .next       = 0
    },
    .flags = 0
};

struct stivale2_tag unmap_null_request = {
    .identifier = STIVALE2_HEADER_TAG_UNMAP_NULL_ID,
    .next       = (uint64_t) &smp_request
};

static stivale2_header_tag_terminal terminal_hdr_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_TERMINAL_ID,
        .next = (uint64_t) &unmap_null_request
    },
    .flags = 0
};

static stivale2_header_tag_framebuffer framebuffer_hdr_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
        .next = (uint64_t) &terminal_hdr_tag
    },
    .framebuffer_width = 0,
    .framebuffer_height = 0,
    .framebuffer_bpp = 0
};

__attribute__((section(".stivale2hdr"), used)) static stivale2_header stivale_hdr = {
    .entry_point = 0,
    .stack = (uintptr_t) stack + sizeof(stack),
    .flags = (1 << 1),
    .tags = (uintptr_t) &framebuffer_hdr_tag
};

void *stivale2_get_tag(stivale2_struct *stivale2_struct, uint64_t id) {
  stivale2_tag *current_tag = (stivale2_tag *) stivale2_struct->tags;

  for (;;) {
    if (current_tag == NULL) {
      return NULL;
    }

    if (current_tag->identifier == id) {
      return current_tag;
    }

    current_tag = (stivale2_tag *) current_tag->next;
  }
}

void stivale2_get_module(stivale2_struct_tag_modules* stivale2_struct, const char *sign, Module *module, size_t headerSize) {
  for (size_t i = 0; i < stivale2_struct->module_count; i++) {
    stivale2_module me = stivale2_struct->modules[i];
    if (strcmp(me.string, sign) == 0) {
      module->header = (void *) me.begin;
      module->body = (void *) (me.begin + headerSize);
      module->size = me.end - me.begin;
    }
  }
}

void stivale2_get_framebuffer(stivale2_struct* stivale2_struct, Framebuffer *framebuffer)
{
  stivale2_struct_tag_framebuffer *fb = (stivale2_struct_tag_framebuffer*)stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);
  if (fb == NULL) return;

  framebuffer->base_address = (void*)fb->framebuffer_addr;
  framebuffer->width = fb->framebuffer_width;
  framebuffer->height = fb->framebuffer_height;
  framebuffer->pitch = fb->framebuffer_pitch;
  framebuffer->bpp = fb->framebuffer_bpp;
}

void printBootloaderInfo(stivale2_struct *stivale2_struct)
{
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
        tm_printf("\tRed mask size:   %d", f->red_mask_size);
        tm_printf("\tRed mask size:   %d", f->red_mask_shift);
        tm_printf("\tGreen mask size: %d", f->green_mask_size);
        tm_printf("\tGreen mask size: %d", f->green_mask_shift);
        tm_printf("\tBlue mask size:  %d", f->blue_mask_size);
        tm_printf("\tBlue mask size:  %d", f->blue_mask_shift);
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
}
