#include "kernel.h"
#include "shell.h"

#define STDIN_FD 0
#define STDOUT_FD 1

static size_t str_len(const char *s)
{
    size_t len = 0;

    while (s[len] != '\0')
    {
        len++;
    }

    return len;
}

int shell_str_eq(const char *lhs, const char *rhs)
{
    size_t i = 0;

    while (lhs[i] != '\0' && rhs[i] != '\0')
    {
        if (lhs[i] != rhs[i])
        {
            return 0;
        }
        i++;
    }

    return lhs[i] == rhs[i];
}

void shell_write(const char *text)
{
    axlib_write(STDOUT_FD, text, str_len(text));
}

static long read_line(char *buf, size_t size)
{
    size_t used = 0;

    if (size == 0)
    {
        return -1;
    }

    while (used + 1 < size)
    {
        char ch = 0;
        long ret = axlib_read(STDIN_FD, &ch, 1);

        if (ret <= 0)
        {
            if (used == 0)
            {
                return ret;
            }
            break;
        }

        if (ch == '\r')
        {
            continue;
        }

        if (ch == '\n')
        {
            break;
        }

        buf[used++] = ch;
    }

    buf[used] = '\0';
    return (long)used;
}

static void show_help(void)
{
    shell_write("commands:\n");
    shell_write("  help      - show this message\n");
    shell_write("  end       - exit shell\n");
}

static void run_command(const char *cmd)
{
    shell_write("unknown command: ");
    shell_write(cmd);
    shell_write("\n");
}

int shell_main(void)
{
    char cmd[SHELL_CMD_BUFFER_SIZE];

    shell_write("axShell started.\n");
    shell_write("type 'help' for commands.\n");

    while (1)
    {
        long read_count;

        shell_write("root@localhost : ");
        read_count = read_line(cmd, sizeof(cmd));

        if (read_count < 0)
        {
            shell_write("\ninput error\n");
            return 1;
        }

        if (read_count == 0)
        {
            shell_write("\n");
            axlib_yield();
            continue;
        }

        if (shell_str_eq(cmd, "end"))
        {
            break;
        }

        if (shell_str_eq(cmd, "help"))
        {
            show_help();
            continue;
        }

        run_command(cmd);
    }

    shell_write("Goodbye, see you next time.\n");
    return 0;
}
