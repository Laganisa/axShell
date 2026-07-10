#include <kernel.h>
#include <string.h>

#include "shell.h"
#include "io.h"
#include "defs.h"

void show_help(void)
{
    str_write("");
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
    
    str_write("unknown command: ");
    str_write(buffer);
    str_write("\n");
}

int shell_main(void)
{

    // 무한 정지
    while (1)
    {
        str_write("user_");
        char buffer[BUFFER_SIZE] = {0,};
        char *arvg[MAX_CMD_TOKEN_LEN];

        read_line(buffer, BUFFER_SIZE);
        uint8_t token_len = parse(buffer,arvg,MAX_CMD_TOKEN_LEN);


        if (axlib_strcmp(buffer, "exit") == 0)
        {
            break;
        }
        execute(buffer);
        switch (execute(buffer))
        {
        case HELP:
            str_write("");
            break;
        case CLEAR:
            str_write("\033[2J\033[H");
            break;
        default:
            str_write("unknown command: ");
            str_write(buffer);
            str_write("\n");
            break;
        }
    }
    return 0;
}