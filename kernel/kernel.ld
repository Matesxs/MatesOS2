ENTRY(_start)

SECTIONS
{
    _KernelBase = 0xffffffff80000000;
    . = _KernelBase + 2M;

    _KernelStart = .;
    .stivale2hdr : {
        KEEP(*(.stivale2hdr))
    }

    .text : {
        *(.text*)
    }

    .rodata : {
        *(.rodata*)
    }

    .data : {
        *(.data*)
    }

    _WritableStart = .;
    .bss : {
        *(COMMON)
        *(.bss*)
    }
    _WritableEnd = .;
    _KernelEnd = .;
}
