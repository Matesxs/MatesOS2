//
// Created by Martin on 02.07.2021.
//

#ifndef MATESOS2_TM_PRINT_HPP
#define MATESOS2_TM_PRINT_HPP

#include "stdarg.h"
#include "stddef.h"
#include "stivale2.h"

extern void (*stivale2_print)(const char *buf, size_t size);

void tm_init();
void tm_disable();
void tm_putc(char c);
void tm_print(const char *msg);
void tm_puts(const char *msg);
void tm_printf(const char *format, ...);

#endif //MATESOS2_TM_PRINT_HPP
