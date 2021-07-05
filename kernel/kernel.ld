ENTRY(_start)

SECTIONS
{
    _virtual_base = 0xffffffff80000000;
    . = _virtual_base + 2M;

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
