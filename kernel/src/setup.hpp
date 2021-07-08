//
// Created by Martin on 02.07.2021.
//

#ifndef MATESOS2_SETUP_HPP
#define MATESOS2_SETUP_HPP

#include "stdint.h"
#include "stivale/stivale2.h"

void preSetup(stivale2_struct *stivale2_struct);
void setupMain();
void postSetup();

extern uint64_t _virtual_base;
extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;
extern uint64_t _WritableStart;
extern uint64_t _WritableEnd;

#endif //MATESOS2_SETUP_HPP
