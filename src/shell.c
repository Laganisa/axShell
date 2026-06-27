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

void test_step3(void)
{
    char buf = 0x00;
    str_write("STEP 3 START: Waiting for input...\n");

    long ret = axlib_read(STDIN_FD, &buf, 1);

    str_write("STEP 3: Read result (ret=");
    int_write((int)ret);
    str_write("), buf=0x");
    hex_write((unsigned int)buf);
    str_write("\n");

    if (ret == 1 && buf != 0x00)
    {
        str_write("STEP 3 SUCCESS!\n");
    }
    else
    {
        str_write("STEP 3 FAIL: Buffer not updated correctly.\n");
    }
}

int shell_main(void)
{
    while (1)
    {
        str_write("A");
    }
}