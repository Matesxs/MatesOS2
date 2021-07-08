//
// Created by Martin on 08.07.2021.
//

#ifndef MATESOS2_IO_HPP
#define MATESOS2_IO_HPP

#include "stdint.h"

#define IO_PIC1_COMMAND	0x20
#define IO_PIC1_DATA	0x21
#define IO_PIC2_COMMAND	0xa0
#define IO_PIC2_DATA	0xa1

#define IO_CHIPSET_ADDRESS_REGISTER	0x22
#define IO_CHIPSET_DATA_REGISTER	  0x23
#define IO_IMCR_REGISTER_ADDRESS	  0x70
#define IO_IMCR_VIA_APIC			      0x01

namespace IO
{
  extern "C" void outb(uint16_t port, uint8_t value);
  extern "C" void outw(uint16_t port, uint16_t value);
  extern "C" void outl(uint16_t port, uint32_t value);

  extern "C" uint8_t inb(uint16_t port);
  extern "C" uint16_t inw(uint16_t port);
  extern "C" uint32_t inl(uint16_t port);

  extern "C" void io_wait();

  extern "C" void io_apic_enable();
  void io_pic_disable();
}

#endif //MATESOS2_IO_HPP
