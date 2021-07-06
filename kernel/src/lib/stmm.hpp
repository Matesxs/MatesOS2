//
// Created by Martin on 02.07.2021.
//

#ifndef MATESOS2_STMM_HPP
#define MATESOS2_STMM_HPP

#include "stdint.h"
#include "stddef.h"

void memset(void *start, uint8_t value, uint64_t num);
void *memcpy(void *__restrict__ dest, const void *__restrict__ src, size_t n);

#endif //MATESOS2_STMM_HPP
