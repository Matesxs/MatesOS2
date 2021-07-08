//
// Created by Martin on 08.07.2021.
//

#ifndef MATESOS2_IO_HPP
#define MATESOS2_IO_HPP

#include "stdint.h"

extern void outb(uint16_t port, uint8_t value);
extern void outw(uint16_t port, uint16_t value);
extern void outl(uint16_t port, uint32_t value);

extern uint8_t inb(uint16_t port);
extern uint16_t inw(uint16_t port);
extern uint32_t inl(uint16_t port);

extern void io_wait();

#endif //MATESOS2_IO_HPP
