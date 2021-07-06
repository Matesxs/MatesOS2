//
// Created by Martin on 02.07.2021.
//

#include "tm_print.hpp"
#include "stddef.h"
#include "stivale_tags_structure.hpp"

void (*stivale2_print)(const char *buf, size_t size) = NULL;

static const char CONVERSION_TABLE[] = "0123456789abcdef";

void tm_init()
{
  stivale2_struct_tag_terminal *terminal_tag = getTags()->terminal_tag;
  if (terminal_tag == NULL)
    while (true) asm("hlt");

  void *term_write_ptr = (void *)terminal_tag->term_write;
  stivale2_print = (void(*)(const char*, size_t))(term_write_ptr);
}

void tm_disable()
{
  stivale2_print = NULL;
}

void tm_putc(char c) {
  if (stivale2_print != NULL)
    stivale2_print(&c, 1);
}

void tm_print(const char *msg) {
  for (size_t i = 0; msg[i]; i++) {
    tm_putc(msg[i]);
  }
}

void tm_puts(const char *msg) {
  tm_print(msg);
  tm_putc('\n');
}

static void tm_printhex(size_t num) {
  int i;
  char buf[17];

  if (!num) {
    tm_print("0x0");
    return;
  }

  buf[16] = 0;

  for (i = 15; num; i--) {
    buf[i] = CONVERSION_TABLE[num % 16];
    num /= 16;
  }

  i++;
  tm_print("0x");
  tm_print(&buf[i]);
}

static void tm_printdec(size_t num) {
  int i;
  char buf[21] = {0};

  if (!num) {
    tm_putc('0');
    return;
  }

  for (i = 19; num; i--) {
    buf[i] = (num % 10) + 0x30;
    num = num / 10;
  }

  i++;
  tm_print(buf + i);
}

void tm_printf(const char *format, ...) {
  va_list argp;
  va_start(argp, format);

  while (*format != '\0') {
    if (*format == '%') {
      format++;
      if (*format == 'x') {
        tm_printhex(va_arg(argp, size_t));
      } else if (*format == 'd') {
        tm_printdec(va_arg(argp, size_t));
      } else if (*format == 's') {
        tm_print(va_arg(argp, char*));
      }
    } else {
      tm_putc(*format);
    }
    format++;
  }

  tm_putc('\n');
  va_end(argp);
}
