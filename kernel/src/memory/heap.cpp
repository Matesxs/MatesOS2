//
// Created by Martin on 12.07.2021.
//

#include "heap.hpp"
#include "../panic.hpp"
#include "paging.hpp"
#include "../logging.hpp"
#include "../lib/stmm.hpp"
#include "memory.hpp"

namespace memory
{
  void *heapStart = NULL;
  void *heapEnd = NULL;

  HeapSegHdr *LastHdr = NULL;
  uint64_t usedPages = 0;
  size_t start_page_count = 0;

  void CreateHeap(void *heapAddress, size_t pageCount)
  {
    if (heapStart != NULL) Panic("Heap already initialized");

    void *pos = heapAddress;

    for (size_t i = 0; i < pageCount; i++)
    {
      void *temp = RequestPage();
      if (temp == NULL) Panic("Cant request heap page");

      MemoryMap(pos, temp);

      pos = (void *)((size_t)pos + PAGE_SIZE);
      usedPages++;
    }

    size_t heapLength = pageCount * PAGE_SIZE;

    heapStart = heapAddress;
    heapEnd = (void *)((size_t)heapStart + heapLength);

    HeapSegHdr *startSeg = (HeapSegHdr *)heapAddress;
    startSeg->length = heapLength - sizeof(HeapSegHdr);
    startSeg->next = NULL;
    startSeg->last = NULL;
    startSeg->free = true;

    LastHdr = startSeg;
    start_page_count = pageCount;
  }

  void WalkHeap()
  {
    logging::log(logging::INFO, "Heap walkthru");

    HeapSegHdr *hdr = (HeapSegHdr*)heapStart;
    uint64_t c = 0;

    while (hdr)
    {
      logging::log(logging::INFOPlus, "[ %d ] Block Addr: %x, Data size: %S, Free: %s, Next block addr: %x", c, hdr, hdr->length, hdr->free ? "True" : "False", hdr->next);
      logging::newln();

      hdr = hdr->next;
      c++;
    }
  }

  HeapSegHdr *HeapSegHdr::Split(size_t splitLength)
  {
    if (splitLength < 0x10)
      return NULL;

    int64_t splitSegLength = length - splitLength - (sizeof(HeapSegHdr));
    if (splitSegLength < 0x10)
      return NULL;

    HeapSegHdr *newSplitHdr = (HeapSegHdr *)((size_t)this + splitLength + sizeof(HeapSegHdr));
    next->last = newSplitHdr;                         // Set the next segment's last segment to our new segment
    newSplitHdr->next = next;                         // Set the new segment's next segment to out original next segment
    next = newSplitHdr;                               // Set our new segment to the new segment
    newSplitHdr->last = this;                         // Set our new segment's last segment to the current segment
    newSplitHdr->length = splitSegLength;             // Set the new header's length to the calculated value
    newSplitHdr->free = free;                         // make sure the new segment's free is the same as the original
    length = splitLength;                             // set the length of the original segment to its new length

    if (LastHdr == this)
      LastHdr = newSplitHdr;

    return newSplitHdr;
  }

  bool ExpandHeap(size_t length)
  {
    length = ROUND_TO_PAGE_SIZE(length);

    size_t pageCount = length / PAGE_SIZE;
    HeapSegHdr *newSegment = (HeapSegHdr *)heapEnd;

    for (size_t i = 0; i < pageCount; i++)
    {
      void *tmp = RequestPage();
      if (tmp == NULL) return false;

      MemoryMap(heapEnd, tmp);

      heapEnd = (void *)((size_t)heapEnd + PAGE_SIZE);
      usedPages++;
    }

    newSegment->free = true;
    newSegment->last = LastHdr;
    LastHdr->next = newSegment;
    LastHdr = newSegment;
    newSegment->next = NULL;
    newSegment->length = length - sizeof(HeapSegHdr);
    newSegment->CombineBackward();

    return true;
  }

  void HeapSegHdr::CombineForward()
  {
    if (next == NULL)
      return;

    if (!next->free)
      return;

    if (next == LastHdr)
      LastHdr = this;

    if (next->next != NULL)
    {
      next->next->last = this;
    }

    length = length + next->length + sizeof(HeapSegHdr);

    next = next->next;
  }

  void HeapSegHdr::CombineBackward()
  {
    if (last != NULL && last->free)
      last->CombineForward();
  }

  void *malloc(size_t size)
  {
    if (size == 0)
      return NULL;

    size = ROUND_UP(size, 0x10);

    HeapSegHdr *currentSeg = (HeapSegHdr *)heapStart;
    while (true)
    {
      if (currentSeg->free)
      {
        size_t curSize = currentSeg->length - sizeof(HeapSegHdr);

        if (curSize > size)
        {
          currentSeg->Split(size);
          currentSeg->free = false;
          return (void *)((uint64_t)currentSeg + sizeof(HeapSegHdr));
        }
        else if (curSize == size)
        {
          currentSeg->free = false;
          return (void *)((uint64_t)currentSeg + sizeof(HeapSegHdr));
        }
      }

      if (currentSeg->next == NULL)
        break;

      currentSeg = currentSeg->next;
    }

    if (!ExpandHeap(size))
      return NULL;

    return malloc(size);
  }

  void *calloc(size_t size)
  {
    if (size == 0)
      return NULL;

    size = ROUND_UP(size, 0x10);

    void *mem = malloc(size);
    if (mem == NULL) return NULL;

    memset(mem, 0, size);
    return mem;
  }

  void free(void *address)
  {
    if (address == NULL) return;

    HeapSegHdr *segment = (HeapSegHdr *)address - 1;
    segment->free = true;
    segment->CombineForward();
    segment->CombineBackward();
  }

  uint64_t GetHeapPages()
  {
    return usedPages;
  }
}

void *operator new(size_t n)
{
  return memory::calloc(n);
}

void *operator new[](size_t s)
{
  return memory::calloc(s);
}

void operator delete(void *p)
{
  memory::free(p);
}

void operator delete[](void *p)
{
  memory::free(p);
}
