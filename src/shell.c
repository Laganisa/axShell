#include <kernel.h>
#include <string.h>

#include "shell.h"
#include "io.h"
#include "defs.h"
#include <call.h>

void show_help(void)
{
    write(STDIO, "%s", "");
}

// 나중에 바꿀 예정
static int execute(const char *buffer)
{

    if (axlib_strcmp(buffer, "help") == 0)
    {
        return HELP;
    }
    if (axlib_strcmp(buffer, "clear") == 0)
    {
        return CLEAR;
    }

    write(STDIO, "%s", "unknown command: ");
    write(STDIO, "%s", buffer);
    write(STDIO, "%s", "\n");
}

int main(void)
{
    debug_main();
    return 0;
}

void debug_main(void)
{
    write(STDIO, "%s", "debug shell main\n");

    file_creat("test", "0777", 4096);

    int fd = file_open("test", 'u', 0);

    write(fd, "%s", "hello world!");

    write(STDIO, "%s", "hello hi\n");

    char ch[2];

    axlib_read(fd, &ch, 1, 0);
    ch[1] = '\0'; // 문자 출력을 위해 널 문자 넣어주기

    write(STDIO, "%s", ch);

    file_close(fd);

    write(STDIO, "%s", "\nshell inf loop\n");
    while (1)
    {
        ;
    }
}

void shell_main(void)
{

    while (1)
    {
        write(STDIO, "%s", "user_");

        char buffer[MAX_CMD_TOKEN_LEN] = {
            0,
        };

        char *arvg[MAX_CMD_TOKEN_LEN];
        read_line(buffer, BUFFER_SIZE);
        uint8_t token_len = parse(buffer, arvg, MAX_CMD_TOKEN_LEN);

        if (axlib_strcmp(buffer, "exit") == 0)
        {
            break;
        }
        execute(buffer);
        switch (execute(buffer))
        {
        case HELP:
            write(STDIO, "%s", "");
            break;
        case CLEAR:
            write(STDIO, "%s", "\033[2J\033[H");
            break;
        default:
            write(STDIO, "%s", "unknown command: ");
            write(STDIO, "%s", buffer);
            write(STDIO, "%s", "\n");
            break;
        }
    }
}