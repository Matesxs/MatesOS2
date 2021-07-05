//
// Created by Martin on 05.07.2021.
//

#ifndef MATESOS2_PAGE_TABLE_HPP
#define MATESOS2_PAGE_TABLE_HPP

#include "stdint.h"

namespace memory {
  enum PageDirectoryFlag {
    PAGE_DIRECTORY_PRESENT = 0,
    PAGE_DIRECTORY_WRITABLE = 1,
    PAGE_DIRECTORY_USERSPACE = 2,
    PAGE_DIRECTORY_WRITETHROUGH = 3,
    PAGE_DIRECTORY_NOCACHE = 4,
    PAGE_DIRECTORY_ACCESSED = 5,
    PAGE_DIRECTORY_LARGERPAGES = 7,
    PAGE_DIRECTORY_OS_AVAILABLE = 11,
    PAGE_DIRECTORY_NOEXECUTE = 63
  };

  struct PageDirectoryEntry {
    uint64_t Value;

    void SetFlag(PageDirectoryFlag flag, bool enabled);

    bool GetFlag(PageDirectoryFlag flag);

    void SetFlags(uint64_t flags);

    uint64_t GetFlags();

    void SetAddress(uint64_t address);

    void Clear();

    uint64_t GetAddress();
  };

  struct PageTable {
    PageDirectoryEntry entries[512];
  } __attribute__((aligned(0x1000)));
}
#endif //MATESOS2_PAGE_TABLE_HPP
