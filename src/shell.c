#include <kernel.h>
#include <string.h>

#include "shell.h"
#include "io.h"
#include "defs.h"

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

int shell_main(void)
{
    test1();

    // 무한 정지
    while (1)
    {
        ;
    }

    return 0;
}