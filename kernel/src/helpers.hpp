//
// Created by Martin on 05.07.2021.
//

#ifndef MATESOS2_HELPERS_HPP
#define MATESOS2_HELPERS_HPP

#include "setup.hpp"
#include "stddef.h"
#include "stdint.h"

#define ROUND_UP(n, multiple)	((n) % (multiple) == 0 ? (n) : (n) - (n) % (multiple) + (multiple))
#define SET_BIT(n, bit, value)	((n) ^ (-(value) ^ (n)) & 1 << (bit))
#define GET_BIT(n, bit)			((1 << (bit) & (n)) > 0)

#define KERNEL_PHYSICAL_ADDRESS(virtual_address)	((void*)((unsigned long long)(virtual_address) - ((unsigned long long)&_virtual_base)))

uint8_t checksum(const char *addr, size_t size) noexcept;

#endif //MATESOS2_HELPERS_HPP
