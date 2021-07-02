//
// Created by Martin on 02.07.2021.
//

#include "stivale_main.hpp"

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
