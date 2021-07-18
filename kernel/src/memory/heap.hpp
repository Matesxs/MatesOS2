//
// Created by Martin on 12.07.2021.
//

#ifndef MATESOS2_HEAP_HPP
#define MATESOS2_HEAP_HPP

#include "stddef.h"
#include "stdint.h"

namespace memory
{
  struct HeapSegHdr
  {
    size_t length;
    HeapSegHdr *next;
    HeapSegHdr *last;
    bool free;
    void CombineForward();
    void CombineBackward();
    HeapSegHdr *Split(size_t splitLength);
  };

  void CreateHeap(void *heapAddress, size_t pageCount);
  void WalkHeap();

  void *malloc(size_t size);
  void *calloc(size_t size);
  void *realloc(void *addr, size_t size);
  void free(void *address);

  bool ExpandHeap(size_t length);

  uint64_t GetHeapPages();
}

void *operator new(size_t n);
void *operator new(size_t n, void *p);
void *operator new[](size_t s);
void operator delete(void *p);
void operator delete[](void *p);

#endif //MATESOS2_HEAP_HPP
