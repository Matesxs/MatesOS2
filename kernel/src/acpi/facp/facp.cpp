#include "facp.hpp"
#include "../../lib/stmm.hpp"
#include "../../logging.hpp"
#include "../../io/io.hpp"
#include "../../helpers.hpp"
#include "../../memory/memory.hpp"

namespace FACP
{
  uint32_t* SMI_CMD;
  uint8_t  ACPI_ENABLE;
  uint8_t  ACPI_DISABLE;
  uint32_t PM1a_CNT;
  uint32_t PM1b_CNT;
  uint16_t SLP_TYPa;
  uint16_t SLP_TYPb;
  uint8_t  PM1_CNT_LEN;
  uint16_t SLP_EN;
  uint16_t SCI_EN;

  uint32_t reset_flag;

  ACPI::FACPHeader *g_FACPHeader = nullptr;

  constexpr uint32_t bake(char a, char b , char c, char d) {
    return a | (b << 8) | (c << 16) | (d << 24);
  }

  void Init(ACPI::FACPHeader *facp)
  {
    g_FACPHeader = facp;

    auto dsdt_addr = (uintptr_t) facp->DSDT;
    constexpr uint32_t DSDT_t = bake('D', 'S', 'D', 'T');

    if (*(uint32_t*)dsdt_addr != DSDT_t)
    {
      logging::log(logging::ERROR, "FACP initialization failed - DSDT baked address missmatch");
      return;
    }

    char* S5Addr = (char*) dsdt_addr + 36;
    int dsdtLength = ((ACPI::SDTHeader*)dsdt_addr)->Length;
    dsdtLength *= 2;

    while (dsdtLength-- > 0)
    {
      if (memcmp(S5Addr, "_S5_", 4) == 0)
        break;
      S5Addr++;
    }

    if (dsdtLength <= 0) {
      logging::log(logging::ERROR, "FACP initialization failed - _S5 not present in ACPI");
      return;
    }

    // check for valid AML structure
    if ( ( *(S5Addr-1) == 0x08 || ( *(S5Addr-2) == 0x08 && *(S5Addr-1) == '\\') ) && *(S5Addr+4) == 0x12 )
    {
      S5Addr += 5;
      S5Addr += ((*S5Addr &0xC0)>>6) + 2;   // calculate PkgLength size

      if (*S5Addr == 0x0A)
        S5Addr++;   // skip byteprefix
      SLP_TYPa = *(S5Addr) << 10;
      S5Addr++;

      if (*S5Addr == 0x0A)
        S5Addr++;   // skip byteprefix
      SLP_TYPb = *(S5Addr)<<10;

      SMI_CMD = (uint32_t*)(uintptr_t) facp->SMI_CMD;

      ACPI_ENABLE = facp->ACPI_ENABLE;
      ACPI_DISABLE = facp->ACPI_DISABLE;

      PM1a_CNT = facp->PM1a_CNT_BLK;
      PM1b_CNT = facp->PM1b_CNT_BLK;

      PM1_CNT_LEN = facp->PM1_CNT_LEN;

      SLP_EN = 1<<13;
      SCI_EN = 1;
    }
    else
    {
      logging::log(logging::ERROR, "FACP Failed to parse _S5");
      SCI_EN = 0;
    }

    logging::log(logging::SUCCESS, "FACP Initialized");
    logging::log(logging::INFOPlus, "FACP Flags: %b\n", facp->Flags);
    logging::log(logging::INFOPlus, "Shutdown enabled: %d, SD addr1: %x, SD addr2: %x, SD value1: %d, SD value2: %d\n", SCI_EN, PM1a_CNT, PM1b_CNT, SLP_TYPa | SLP_EN, SLP_TYPb | SLP_EN);

    const char *addrSpace;
    switch (facp->RESET_REG.AddressSpace) {
      case ACPI::IO:
        addrSpace = "IO";
        break;

      case ACPI::MMIO:
        addrSpace = "Memory";
        break;

      case ACPI::PCI:
        addrSpace = "PCI";
        break;
    }

    reset_flag = GET_BIT(facp->Flags, 10);
    logging::log(logging::INFOPlus, "Reset enabled: %d, Reset addr: %x, Reset value: %d, Address space: %s\n", reset_flag, facp->RESET_REG.Address, facp->RESET_VALUE, addrSpace);
  }

  __attribute__((noreturn))
  void Shutdown()
  {
    asm volatile ("cli");

    if (SCI_EN)
    {
      IO::outw(PM1a_CNT, SLP_TYPa | SLP_EN);
      if (PM1b_CNT != 0)
        IO::outw(PM1b_CNT, SLP_TYPb | SLP_EN);
    }

    // Next code works only in virtual environment and is there only as backup if normal ACPI shutdown failed

    // Shudown old QEMU and Bochs
    IO::outw(0xB004, 0x2000);

    // Shudown new QEMU
    IO::outw(0x604, 0x2000);

    // Shutdown Virtualbox
    IO::outw(0x4004, 0x3400);

    while (true) asm ("hlt");
  }

  __attribute__((noreturn))
  void Reboot()
  {
    asm volatile ("cli");

    if (reset_flag)
    {
      switch (g_FACPHeader->RESET_REG.AddressSpace)
      {
        case ACPI::IO:
          IO::outb(g_FACPHeader->RESET_REG.Address, g_FACPHeader->RESET_VALUE);
          break;

        case ACPI::MMIO:
          memory::IdentityMap((void*)g_FACPHeader->RESET_REG.Address);
          *((volatile uint8_t *) ((uintptr_t)g_FACPHeader->RESET_REG.Address)) = g_FACPHeader->RESET_VALUE;
          break;

        case ACPI::PCI:
          // TODO: Implement
          logging::log(logging::WARNING, "PCI reset is not implemented!");
          break;
      
        default:
          break;
      }
    }

    while (true) asm ("hlt");
  }
}