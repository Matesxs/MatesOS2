//
// Created by Martin on 05.07.2021.
//

#ifndef MATESOS2_MEMORY_FRAME_HPP
#define MATESOS2_MEMORY_FRAME_HPP

#include "stdint.h"
#include "stddef.h"

namespace memory
{
  #define PAGEFRAME_INITIAL_RESERVE_PAGES	256

  void InitPageframe();

  void *RequestPage();
  void *ReqestPages(size_t pages);

  void PageframeUnlock(void *phys_addr, size_t pages);
  void PageframeLock(void *phys_addr, size_t pages);

  void PageframeUnreserve(void *phys_addr, size_t pages);
  void PageframeReserve(void *phys_addr, size_t pages);
  void PageframeReserveSize(void *phys_addr, size_t size);

  size_t GetTotalMemory();
  size_t GetFreeMemory();
  size_t GetReservedMemory();
  size_t GetUsedMemory();
}

#endif //MATESOS2_MEMORY_FRAME_HPP
