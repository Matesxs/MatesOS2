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
}