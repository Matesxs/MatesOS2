ENTRY(_start)

SECTIONS
{
    . = 0xffffffff80200000;

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
