.section .text.start
.global _start

_start:
    bl shell_main
    mov w0, w0 // nop
    bl axlib_exit

1:
    b 1b
