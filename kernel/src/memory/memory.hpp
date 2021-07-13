//
// Created by Martin on 05.07.2021.
//

#ifndef MATESOS2_MEMORY_HPP
#define MATESOS2_MEMORY_HPP

#include "../helpers.hpp"
#include "memory_frame.hpp"
#include "paging.hpp"
#include "heap.hpp"

namespace memory
{
  #define PAGE_SIZE 4096
  #define ROUND_TO_PAGE_SIZE(am) (ROUND_UP(am, PAGE_SIZE))
  #define	NEAREST_PAGE_COUNT(n) (ROUND_TO_PAGE_SIZE(n) / PAGE_SIZE)
}

#endif //MATESOS2_MEMORY_HPP
