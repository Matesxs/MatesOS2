//
// Created by Martin on 02.07.2021.
//

#include "stivale/stivale_main.hpp"
#include "helpers.hpp"

extern "C" void _start(stivale2_struct *stivale2_struct)
{
  stivale2_struct_tag_terminal *term_str_tag = (stivale2_struct_tag_terminal *)stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_TERMINAL_ID);
  if (term_str_tag == NULL) return halt();

  void *term_write_ptr = (void *)term_str_tag->term_write;
  void (*term_write)(const char *string, size_t length) = (void(*)(const char*, size_t))(term_write_ptr);

  term_write("Hello World", 11);

  halt();
}