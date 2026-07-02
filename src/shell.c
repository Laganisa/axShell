#include <kernel.h>
#include <string.h>

#include "shell.h"
#include "io.h"
#include "defs.h"

#include "uart_io.h"

static void show_help(void)
{
    // 도움 코드 작성
}

// 나중에 바꿀 예정
static void run_command(const char *cmd)
{
    str_write("unknown command: ");
    str_write(cmd);
    str_write("\n");
}

void foo()
{
    volatile uint32_t *uart_dr = (uint32_t *)0x09000000;

    *uart_dr = 'O';
}

int shell_main(void)
{
    volatile uint32_t *uart_dr = (uint32_t *)0x09000000;

    *uart_dr = 'H';
    foo();
    str_write("SADSDA");

    while (1)
    {
        ;
    }
    return 0;
}