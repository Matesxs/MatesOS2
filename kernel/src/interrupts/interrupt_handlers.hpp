//
// Created by Martin on 06.07.2021.
//

#ifndef MATESOS2_INTERRUPT_HANDLERS_HPP
#define MATESOS2_INTERRUPT_HANDLERS_HPP

struct interrupt_frame;
__attribute__((interrupt, noreturn)) void PageFault_Handler(interrupt_frame *frame);
__attribute__((interrupt, noreturn)) void DoubleFault_Handler(interrupt_frame *frame);
__attribute__((interrupt, noreturn)) void GPFault_Handler(interrupt_frame *frame);

#endif //MATESOS2_INTERRUPT_HANDLERS_HPP
