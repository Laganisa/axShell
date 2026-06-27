ENTRY(_start)

SECTIONS
{
    . = 0x40096810;

    .text : ALIGN(16) {
        *(.text.start)
        *(.text*)
    }

    .data : ALIGN(16) {
        *(.data*)
    }

    .bss : ALIGN(16) {
        __bss_start = .;
        *(.bss*)
        *(COMMON)
        __bss_end = .;
    }

    /DISCARD/ : {
        *(.comment*)
        *(.note*)
        *(.eh_frame*)
    }
}