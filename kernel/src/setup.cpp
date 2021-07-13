//
// Created by Martin on 02.07.2021.
//

#include "setup.hpp"
#include "memory/memory.hpp"
#include "stivale/tm_print.hpp"
#include "stivale/stivale_tags_structure.hpp"
#include "renderer/basic_renderer.hpp"
#include "logging.hpp"
#include "interrupts/interrupt.hpp"
#include "interrupts/interrupt_handlers.hpp"
#include "gdt/gdt.hpp"
#include "panic.hpp"
#include "acpi/acpi.hpp"
#include "cpu/cpuid/features.hpp"
#include "cpu/cpuid/cpuInfo.hpp"
#include "drivers/driver.hpp"
#include "lib/stmm.hpp"
#include "memory/heap.hpp"

void printCPUInfo()
{
  CPU::CPUInfo cpuInfo = CPU::GetCPUInfo();

  logging::log(logging::INFOPlus, "Vendor: %s (%d)", cpuInfo.VendorString, cpuInfo.VendorID);
  logging::newln();

  logging::log(logging::INFOPlus, "Brand: %s", cpuInfo.BrandString);
  logging::newln();

  logging::log(logging::INFOPlus, "Features: ");
  if (CPU::feature::APIC()) logging::log(logging::INFOPlusC, "APIC ");
  if (CPU::feature::FPU()) logging::log(logging::INFOPlusC, "FPU ");
  if (CPU::feature::X2APIC()) logging::log(logging::INFOPlusC, "X2APIC ");
  if (CPU::feature::SSE()) logging::log(logging::INFOPlusC, "SSE ");
  logging::newln();
}

void setupInterrupts()
{
  interrupts::Init();
  interrupts::InitExceptions();
  interrupts::InitPICHandler();
  interrupts::Load();
  logging::log(logging::SUCCESS, "Interrupts initialized");
}

void setupMemory()
{
  Framebuffer fb = getTags()->framebuffer;
  size_t framebufferSize = fb.pitch * fb.height;

  memory::InitPageframe();
  memory::PageframeReserveSize((void*)fb.base_address, framebufferSize);
  logging::log(logging::SUCCESS, "Pageframe loaded");
  logging::log(logging::INFOPlus, "Total memory: %S\n", memory::GetTotalMemory());
  logging::log(logging::INFOPlus, "Free memory:  %S\n", memory::GetFreeMemory());
  logging::log(logging::INFOPlus, "Reserved memory: %S\n", memory::GetReservedMemory());

  memory::InitPaging();
  memory::IdentityMapSize((void*)fb.base_address, framebufferSize);
  memory::SetWritableSize((void*)fb.base_address, framebufferSize);
  memory::PageTable *l4_table = memory::GetL4Table();
  if (l4_table == NULL) Panic("No L4 table returned");

  asm("mov %0, %%cr3" : : "r"(l4_table));
  logging::log(logging::SUCCESS, "Paging initialized");

  memory::CreateHeap((void*)HEAP_BASE, 0x10);
  logging::log(logging::SUCCESS, "Heap Initialized");
  logging::log(logging::INFOPlus, "Heap pages: %d, Start size: %S\n", memory::GetHeapPages(), memory::GetHeapPages() * PAGE_SIZE);
}

void setupACPI()
{
  stivale2_struct_tag_rsdp *rsdpTag = getTags()->rsdp;
  if (rsdpTag == NULL) return Panic("RSDP tag not found");

  ACPI::RSDP2 *rsdp = (ACPI::RSDP2*)rsdpTag->rsdp;
  if (rsdp == NULL) return Panic("RSDP Table not found");

  logging::log(logging::INFO, "RSDP Table found");
  logging::log(logging::INFOPlus, "Revision: %d", rsdp->Revision);
  logging::newln();

  ACPI::SDTHeader *rootHeader = NULL;
  void *(*FindTable)(ACPI::SDTHeader*, char*) = NULL;

  if (rsdp->Revision >= 2)
  {
    // XSDT available
    logging::log(logging::INFO, "Using XSDT");
    rootHeader = (ACPI::SDTHeader*)(rsdp->XSDTAddress);
    FindTable = &ACPI::FindXSDTTable;

    ACPI::EnumXSDT(rootHeader);
  }
  else
  {
    // XSDT available
    logging::log(logging::INFO, "Using RSDT");
    rootHeader = (ACPI::SDTHeader*)(uint64_t)(rsdp->RSDTAddress);
    FindTable = &ACPI::FindRSDTTable;

    ACPI::EnumRSDT(rootHeader);
  }

  if (rootHeader == NULL) return Panic("Root ACPI header not found");

  ACPI::FACPHeader *facp = (ACPI::FACPHeader*)FindTable(rootHeader, (char*)"FACP");
  if (facp == NULL) return Panic("FACP Table not found");
}

void preSetup(stivale2_struct *stivale2_struct)
{
  // Clear writable part of kernel in case there is some garbage
  memset(&_WritableStart, 0, (uint64_t)&_WritableEnd - (uint64_t)&_WritableStart);

  // Init basic functionality from bootloader
  getTags(stivale2_struct);
  tm_init();
  printBootloaderInfo(stivale2_struct);

  if (!BasicRenderer::InitBasicRenderer())
  {
    tm_printf("[PANIC] Failed to init basic renderer");
    while (true) asm("hlt");
  }
  BasicRenderer::ClearScreen();
  BasicRenderer::SetCursor(4, 0);

  Framebuffer *fb = BasicRenderer::GetFramebuffer();
  logging::log(logging::SUCCESS, "Basic Renderer initialized");
  logging::log(logging::INFOPlus, "Addr: %x, Size: %S\n", (uint64_t)fb, fb->pitch * fb->height);
  logging::log(logging::INFOPlus, "Resolution: %dx%d, Bpp: %d\n", fb->width, fb->height, fb->bpp);

  CPU::feature::cpu_enable_features();
  logging::log(logging::SUCCESS, "CPU Info loaded");
  printCPUInfo();

  tm_disable(); // We can disable stivale terminal because now we have framebuffer
  GDTBlock *gtd_block = GDTInit();
  LoadGDT(&gtd_block->descriptor);
  logging::log(logging::SUCCESS, "GDT Loaded");

  setupInterrupts();
}

void setupMain()
{
  setupMemory();
  setupACPI();
}

void postSetup()
{
  if (driver::g_DriverManager.get_num_of_drivers() > 0) driver::g_DriverManager.activate_all();
  else logging::log(logging::WARNING, "No drivers to load");

  memory::WalkHeap();
}
