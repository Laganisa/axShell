.section .text.start
.global _start

_start:
    bl shell_main
    mov w0, w0
    bl mylib_exit

1:
    b 1b
