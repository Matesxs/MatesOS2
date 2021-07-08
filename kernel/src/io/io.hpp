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

#define IO_ICW1_INIT	0x10
#define IO_ICW1_ICW4	0x01
#define IO_ICW4_8086	0x01

#define IO_CHIPSET_ADDRESS_REGISTER	0x22
#define IO_CHIPSET_DATA_REGISTER	  0x23
#define IO_IMCR_REGISTER_ADDRESS	  0x70
#define IO_IMCR_8259_DIRECT			    0x00
#define IO_IMCR_VIA_APIC			      0x01

#define IO_PIC_EOI 0x20

#define IRQ_NUM 16
#define IRQ_PIC_OFFSET 0x20

#define IO_IRQ_TIMER 0
#define IO_IRQ_KEYBOARD 1
#define IO_IRQ_TO_SLAVE_PIC 2
#define IO_IRQ_COM2_4 3
#define IO_IRQ_COM1_3 4
#define IO_IRQ_LPT2 5
#define IO_IRQ_FLOPPY 6
#define IO_IRQ_LPT1 7
#define IO_IRQ_REAL_TIME_CLOCK 8
#define IO_IRQ_AVAILABLE_1 9
#define IO_IRQ_AVAILABLE_2 10
#define IO_IRQ_AVAILABLE_3 11
#define IO_IRQ_MOUSE 12
#define IO_IRQ_MATH_CPU 13
#define IO_IRQ_FIRST_HD 14
#define IO_IRQ_SECOND_HD 15

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
  int io_pic_irq_enable(uint32_t irq);
  int io_pic_irq_disable(uint32_t irq);
  void io_pic_remap();
  void io_pic_end_master();
  void io_pic_end_slave();
}

#endif //MATESOS2_IO_HPP
