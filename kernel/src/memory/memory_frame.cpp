//
// Created by Martin on 05.07.2021.
//

#include "memory_frame.hpp"
#include "bitmap.hpp"
#include "memory.hpp"
#include "../stivale/stivale_tags_structure.hpp"

namespace memory
{
  static size_t s_memory_total_size = 0;
  static size_t s_memory_used_size = 0;
  static size_t s_memory_reserved_size = 0;

  static Bitmap s_pageframemap;

  static size_t s_current_index = 0;

  void InitPageframe()
  {
    StivaleTags *tags = getTags();

    stivale2_mmap_entry *memmap = tags->memory_tag->memmap;
    size_t entries = tags->memory_tag->entries;

    stivale2_mmap_entry *largestPrimary = NULL;
    size_t largestPageCount = 0;

    for (size_t i = 0; i < entries; i++)
    {
      stivale2_mmap_entry *currentEntry = memmap + i;
      size_t num_of_pages = NEAREST_PAGE_COUNT(currentEntry->length);

      if (currentEntry->type == STIVALE2_MMAP_USABLE &&
          (largestPrimary == NULL || num_of_pages > largestPageCount))
      {
        largestPrimary = currentEntry;
        largestPageCount = num_of_pages;
      }

      s_memory_total_size += num_of_pages * PAGE_SIZE;
    }

    s_pageframemap.BitmapInit((uint8_t*)largestPrimary->base, s_memory_total_size / PAGE_SIZE / BITMAP_SCALE);
    PageframeReserve(0, s_memory_total_size / PAGE_SIZE);

    for (size_t i = 0; i < entries; i++)
    {
      stivale2_mmap_entry *currentEntry = memmap + i;
      size_t num_of_pages = NEAREST_PAGE_COUNT(currentEntry->length);

      if (currentEntry->type != STIVALE2_MMAP_USABLE) continue;

      PageframeUnreserve((void*)currentEntry->base, num_of_pages);
    }

    PageframeLock(s_pageframemap.GetBuffer(), NEAREST_PAGE_COUNT(s_pageframemap.GetSize()));

    size_t kernel_size = (size_t)&_KernelEnd - (size_t)&_KernelStart;
    size_t kernel_pages = NEAREST_PAGE_COUNT(kernel_size);
    PageframeLock(KERNEL_PHYSICAL_ADDRESS(&_KernelStart), kernel_pages);

    PageframeReserve(0, PAGEFRAME_INITIAL_RESERVE_PAGES);
  }

  void *RequestPage()
  {
    size_t bitmapSize = s_pageframemap.GetRealSize();

    for (; s_current_index < bitmapSize; s_current_index++)
    {
      // if not free
      if (s_pageframemap[s_current_index]) continue;

      void *page = (void*)(s_current_index * PAGE_SIZE);
      s_current_index++;

      PageframeLock(page, 1);
      return page;
    }

    // TODO: Make swap to disk
    return NULL;
  }

  void *ReqestPages(size_t pages)
  {
    size_t bitmapSize = s_pageframemap.GetRealSize();

    while (s_current_index < bitmapSize)
    {
      for (size_t j = 0; j < pages; j++)
      {
        if (s_pageframemap[s_current_index + j])
        {
          s_current_index += j + 1;
          goto not_free;
        }
      }
      goto exit;

      not_free:
      continue;

      exit:
      void *page = (void*)(s_current_index * PAGE_SIZE);
      s_current_index += pages;
      PageframeLock(page, pages);
      return page;
    }

    // TODO: Make swap to disk
    return NULL;
  }

  bool pageframe_manipulate(uint64_t index, bool state)
  {
    if(s_pageframemap[index] == state)
    {
      return true;
    }
    return s_pageframemap.Set(index, state);
  }

  void PageframeUnlock(void *phys_addr, size_t pages)
  {
    uint64_t start = (uint64_t)phys_addr / PAGE_SIZE;

    for(uint64_t i = start; i < start + pages; i++)
    {
      if (pageframe_manipulate(i, false))
      {
        if (s_memory_used_size >= PAGE_SIZE)
        {
          s_memory_used_size -= PAGE_SIZE;
        }

        if (s_current_index > i)
          s_current_index = i;
      }
    }
  }

  void PageframeLock(void *phys_addr, size_t pages)
  {
    uint64_t start = (uint64_t)phys_addr / PAGE_SIZE;

    for(uint64_t i = start; i < start + pages; i++)
    {
      if (pageframe_manipulate(i, true))
      {
        s_memory_used_size += PAGE_SIZE;
      }
    }
  }

  void PageframeUnreserve(void *phys_addr, size_t pages)
  {
    uint64_t start = (uint64_t)phys_addr / PAGE_SIZE;

    for(uint64_t i = start; i < start + pages; i++)
    {
      if (pageframe_manipulate(i, false))
      {
        if (s_memory_reserved_size >= PAGE_SIZE)
        {
          s_memory_reserved_size -= PAGE_SIZE;
        }

        if (s_current_index > i)
          s_current_index = i;
      }
    }
  }

  void PageframeReserve(void *phys_addr, size_t pages)
  {
    uint64_t start = (uint64_t)phys_addr / PAGE_SIZE;

    for(uint64_t i = start; i < start + pages; i++)
    {
      if (pageframe_manipulate(i, true))
      {
        s_memory_reserved_size += PAGE_SIZE;
      }
    }
  }

  void PageframeReserveSize(void *phys_addr, size_t size)
  {
    PageframeReserve(phys_addr, NEAREST_PAGE_COUNT(size));
  }

  size_t GetTotalMemory()
  {
    return s_memory_total_size;
  }

  size_t GetFreeMemory()
  {
    return s_memory_total_size - s_memory_used_size - s_memory_reserved_size;
  }

  size_t GetReservedMemory()
  {
    return s_memory_reserved_size;
  }

  size_t GetUsedMemory()
  {
    return s_memory_used_size;
  }
}