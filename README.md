# MatesOS2

## Table of contents
- [Table of contents](#table-of-contents)
- [General info](#general-info)
- [Features](#features)  
- [Developement environment](#developement-environment)
- [Screenshots](#screenshots)

## General info
My second attept of creating my own OS. This time I am using limine bootloader with stivale2. \
This OS has x86_64 architecture and its written mainly in C++. \
It is still not finished and here is lack of support for hardware run of this OS and most of the features OS should have.

## Features
- Basic renderer with PSF1 font, grid system, scrolling and string printf-like string formating
- Screen logging (logging to serial is on TODO list)
- Memory management with 4 level paging
- Block based heap
- Simple exception handling
- Custom GDT
- PS/2 Keyboard support
- FACP
- PCI

## Developement environment
### Software
- WSL (Ubuntu-20.04)
    - **nasm** for compiling assembler code
    - **gcc** for compiling C++ code
    - **ld** as a linker
    - **QEMU** for virtual machine

### Hardware
I7 - 9700KF \
32GB 3200MHz RAM \
RTX 2080S

## Screenshots
![scr1](media/scr1.jpg?raw=true)