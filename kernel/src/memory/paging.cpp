//
// Created by Martin on 05.07.2021.
//

#include "paging.hpp"
#include "../lib/stmm.hpp"
#include "memory.hpp"
#include "../stivale/stivale_tags_structure.hpp"

namespace memory
{
  static PageTable *l4_page = NULL;

  PageMapIndexer::PageMapIndexer(uint64_t virtualAddress)
  {
    virtualAddress >>= 12;
    l1_i = virtualAddress & 0x1ff;
    virtualAddress >>= 9;
    l2_i = virtualAddress & 0x1ff;
    virtualAddress >>= 9;
    l3_i = virtualAddress & 0x1ff;
    virtualAddress >>= 9;
    l4_i = virtualAddress & 0x1ff;
  }

  void InitPaging()
  {
    l4_page = (PageTable*)RequestPage();
    memset((void*)l4_page, 0, PAGE_SIZE);

    void* kernel_physical_start = KERNEL_PHYSICAL_ADDRESS(&_KernelStart);
    void* kernel_physical_end = KERNEL_PHYSICAL_ADDRESS(&_KernelEnd);
    void* kernel_writable_physical_start = KERNEL_PHYSICAL_ADDRESS(&_WritableStart);
    void* kernel_writable_physical_end = KERNEL_PHYSICAL_ADDRESS(&_WritableEnd);
    uint64_t kernel_virtual_base = (uint64_t)&_virtual_base;

    // Map kernel
    for(uint64_t ptr = (uint64_t)kernel_physical_start; ptr < (uint64_t)kernel_physical_end; ptr += PAGE_SIZE)
    {
      void* virtual_address = (void*)(ptr + kernel_virtual_base);
      MemoryMap(virtual_address, (void*)ptr);

      if(ptr >= (uint64_t)kernel_writable_physical_start && ptr < (uint64_t)kernel_writable_physical_end)
      {
        SetWritable((void*)virtual_address, 1);
      }
    }

    // Map useable memory regions
    StivaleTags *tags = getTags();

    stivale2_mmap_entry* memorymap = tags->memory_tag->memmap;
    size_t entries_num = tags->memory_tag->entries;

    for(size_t i = 0; i < entries_num; i++) {
      stivale2_mmap_entry* memorymap_entry = memorymap + i;
      if(memorymap_entry->type != STIVALE2_MMAP_USABLE) continue;

      IdentityMap((void*)memorymap_entry->base, NEAREST_PAGE_COUNT(memorymap_entry->length));
      SetWritable((void*)memorymap_entry->base, NEAREST_PAGE_COUNT(memorymap_entry->length));
    }

    // Map rest of memory regions
    IdentityMapSize((void*)0, GetTotalMemory());
  }

  void MemoryMap(void* virtual_addr, void* phys_addr)
  {
    PageMapIndexer indexer = PageMapIndexer((uint64_t)virtual_addr);

    PageTable* pagetable_l3;
    PageTable* pagetable_l2;
    PageTable* pagetable_l1;
    PageDirectoryEntry entry;

    entry = l4_page->entries[indexer.l4_i];
    if (!entry.GetFlag(PAGE_DIRECTORY_PRESENT))
    {
      // page is not present
      pagetable_l3 = (PageTable*)RequestPage();
      memset(pagetable_l3, 0, PAGE_SIZE);
      entry.SetAddress((uint64_t)pagetable_l3 >> 12);
      entry.SetFlag(PAGE_DIRECTORY_PRESENT, true);
      l4_page->entries[indexer.l4_i] = entry;
    }
    else
    {
      // page is present
      pagetable_l3 = (PageTable*)((uint64_t)entry.GetAddress() << 12);
    }

    entry = pagetable_l3->entries[indexer.l3_i];
    if (!entry.GetFlag(PAGE_DIRECTORY_PRESENT))
    {
      // page not present
      pagetable_l2 = (PageTable*)RequestPage();
      memset(pagetable_l2, 0, PAGE_SIZE);
      entry.SetAddress((uint64_t)pagetable_l2 >> 12);
      entry.SetFlag(PAGE_DIRECTORY_PRESENT, true);
      pagetable_l3->entries[indexer.l3_i] = entry;
    }
    else
    {
      // page present
      pagetable_l2 = (PageTable*)((uint64_t)entry.GetAddress() << 12);
    }

    entry = pagetable_l2->entries[indexer.l2_i];
    if (!entry.GetFlag(PAGE_DIRECTORY_PRESENT))
    {
      // page not present
      pagetable_l1 = (PageTable*)RequestPage();
      memset(pagetable_l1, 0, PAGE_SIZE);
      entry.SetAddress((uint64_t)pagetable_l1 >> 12);
      entry.SetFlag(PAGE_DIRECTORY_PRESENT, true);
      pagetable_l2->entries[indexer.l2_i] = entry;
    }
    else
    {
      // page present
      pagetable_l1 = (PageTable*)((uint64_t)entry.GetAddress() << 12);
    }

    entry = pagetable_l1->entries[indexer.l1_i];
    entry.SetAddress((uint64_t)phys_addr >> 12);
    entry.SetFlag(PAGE_DIRECTORY_PRESENT, true);
    pagetable_l1->entries[indexer.l1_i] = entry;
  }

  void MemoryMap(void* virtual_addr, void* phys_addr, size_t pages)
  {
    for (size_t i = 0; i < pages; i++)
    {
      MemoryMap((void*)((uint64_t)virtual_addr + i * PAGE_SIZE), (void*)((uint64_t)phys_addr + i * PAGE_SIZE));
    }
  }

  void IdentityMap(void *addr, size_t pages)
  {
    for(uint64_t ptr = (uint64_t)addr; ptr < (uint64_t)addr + pages * PAGE_SIZE; ptr += PAGE_SIZE)
    {
      MemoryMap((void*)ptr, (void*)ptr);
    }
  }

  void IdentityMapSize(void *addr, size_t size)
  {
    IdentityMap(addr, NEAREST_PAGE_COUNT(size));
  }

  void SetAttribute(void* virtual_address, size_t pages, PageDirectoryFlag attribute, bool enabled)
  {
    for (size_t i = 0; i < pages; i++)
    {
      PageDirectoryEntry entry;
      PageMapIndexer indexes((uint64_t)virtual_address + (i * PAGE_SIZE));

      entry = l4_page->entries[indexes.l4_i];
      entry.SetFlag(attribute, enabled);
      l4_page->entries[indexes.l4_i] = entry;

      PageTable *pagetable_l3 = (PageTable*)((uint64_t)entry.GetAddress() << 12);
      entry = pagetable_l3->entries[indexes.l3_i];
      entry.SetFlag(attribute, enabled);
      pagetable_l3->entries[indexes.l3_i] = entry;

      PageTable *pagetable_l2 = (PageTable*)((uint64_t)entry.GetAddress() << 12);
      entry = pagetable_l2->entries[indexes.l2_i];
      entry.SetFlag(attribute, enabled);
      pagetable_l2->entries[indexes.l2_i] = entry;

      PageTable *pagetable_l1 = (PageTable*)((uint64_t)entry.GetAddress() << 12);
      entry = pagetable_l1->entries[indexes.l1_i];
      entry.SetFlag(attribute, enabled);
      pagetable_l1->entries[indexes.l1_i] = entry;
    }
  }

  void SetWritable(void* virtual_address, size_t pages)
  {
    SetAttribute(virtual_address, pages, PAGE_DIRECTORY_WRITABLE, true);
  }
  void SetWritableSize(void* virtual_address, size_t size)
  {
    SetWritable(virtual_address, NEAREST_PAGE_COUNT(size));
  }

  PageTable *GetL4Table()
  {
    return l4_page;
  }
}