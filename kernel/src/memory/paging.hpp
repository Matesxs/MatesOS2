//
// Created by Martin on 05.07.2021.
//

#ifndef MATESOS2_PAGING_HPP
#define MATESOS2_PAGING_HPP

#include "page_table.hpp"
#include "stddef.h"
#include "memory_frame.hpp"

namespace memory
{
  class PageMapIndexer
  {
  public:
    PageMapIndexer(uint64_t virtualAddress);
    uint64_t l4_i;
    uint64_t l3_i;
    uint64_t l2_i;
    uint64_t l1_i;
  };

  void InitPaging();
  void MemoryMap(void* virtual_addr, void* phys_addr);
  void MemoryMap(void* virtual_addr, void* phys_addr, size_t pages);
  void IdentityMap(void *addr, size_t pages);
  void IdentityMapSize(void *addr, size_t size);

  void SetAttribute(void* virtual_address, size_t pages, PageDirectoryFlag attribute, bool enabled);
  void SetWritable(void* virtual_address, size_t pages);
  void SetWritableSize(void* virtual_address, size_t size);

  PageTable *GetL4Table();
}

#endif //MATESOS2_PAGING_HPP
