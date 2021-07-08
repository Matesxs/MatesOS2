//
// Created by Martin on 08.07.2021.
//

#include "io.hpp"

namespace IO
{
  void io_pic_disable()
  {
    // Redirect
    outb(IO_CHIPSET_ADDRESS_REGISTER, IO_IMCR_REGISTER_ADDRESS);
    io_wait();
    outb(IO_CHIPSET_DATA_REGISTER, IO_IMCR_VIA_APIC);
    io_wait();
    // Disable
    outb(IO_PIC1_DATA, 0xff);
    io_wait();
    outb(IO_PIC2_DATA, 0xff);
  }

  void io_pic_remap()
  {
    // Original PIC data
    uint8_t d1 = inb(IO_PIC1_DATA);
    io_wait();
    uint8_t d2 = inb(IO_PIC2_DATA);
    io_wait();
    // Tell PIC's to start the initialization sequence
    outb(IO_PIC1_COMMAND, IO_ICW1_INIT | IO_ICW1_ICW4);
    io_wait();
    outb(IO_PIC2_COMMAND, IO_ICW1_INIT | IO_ICW1_ICW4);
    io_wait();
    // Tell each PIC their offset
    outb(IO_PIC1_DATA, IRQ_PIC_OFFSET);
    io_wait();
    outb(IO_PIC2_DATA, IRQ_PIC_OFFSET + 8);
    io_wait();
    outb(IO_PIC1_DATA, 0x04);
    io_wait();
    outb(IO_PIC2_DATA, 0x02);
    io_wait();
    outb(IO_PIC1_DATA, IO_ICW4_8086);
    io_wait();
    outb(IO_PIC2_DATA, IO_ICW4_8086);
    io_wait();
    // Restore saved data
    outb(IO_PIC1_DATA, d1);
    io_wait();
    outb(IO_PIC2_DATA, d2);
  }

  int io_pic_irq_enable(uint32_t irq)
  {
    if (irq >= IRQ_NUM) {
      return -1;
    }

    uint8_t cur_mask;
    uint8_t new_mask;

    if (irq < 8) {
      new_mask = ~(1 << irq);
      cur_mask = inb(IO_PIC1_DATA);
      outb(IO_PIC1_DATA, (new_mask & cur_mask));
    } else {
      irq -= 8;
      new_mask = ~(1 << irq);
      cur_mask = inb(IO_PIC2_DATA);
      outb(IO_PIC2_DATA, (new_mask & cur_mask));
    }

    return 0;
  }

  int io_pic_irq_disable(uint32_t irq)
  {
    if (irq >= IRQ_NUM) {
      return -1;
    }

    uint8_t cur_mask;
    if (irq < 8) {
      cur_mask = inb(IO_PIC1_DATA);
      cur_mask |= (1 << irq);
      outb(IO_PIC1_DATA, cur_mask & 0xFF);
    } else {
      irq = irq - 8;
      cur_mask = inb(IO_PIC2_DATA);
      cur_mask |= (1 << irq);
      outb(IO_PIC2_DATA, cur_mask & 0xFF);
    }
    return 0;
  }

  void io_pic_end_master()
  {
    outb(IO_PIC1_COMMAND, IO_PIC_EOI);
  }

  void io_pic_end_slave()
  {
    outb(IO_PIC2_COMMAND, IO_PIC_EOI);
    outb(IO_PIC1_COMMAND, IO_PIC_EOI);
  }
}