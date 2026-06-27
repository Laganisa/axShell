#include <kernel.h>

#include "io.h"
#include "defs.h"

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

/*
void str_write(const char *text)
{
    axlib_write(STDOUT_FD, text, str_len(text));
}
*/

void str_write(const char *text)
{
    while (*text != '\0')
    {
        char temp = *text;
        axlib_write(STDOUT_FD, &temp, 1);
        text++;
    }
}

void int_write(int n)
{
    if (n == 0)
    {
        str_write("0");
        return;
    }

    char buf[12];
    int i = 0;
    int is_negative = 0;

    if (n < 0)
    {
        is_negative = 1;
        n = -n;
    }

    while (n > 0)
    {
        buf[i++] = (n % 10) + '0';
        n /= 10;
    }

    if (is_negative)
        buf[i++] = '-';

    for (int j = 0; j < i; j++)
    {
        char c = buf[i - 1 - j];
        axlib_write(STDOUT_FD, &c, 1);
    }
}

void hex_write(unsigned int n)
{
    if (n == 0)
    {
        str_write("0");
        return;
    }

    char buf[10];
    int i = 0;
    char hex_chars[] = "0123456789ABCDEF";

    while (n > 0)
    {
        buf[i++] = hex_chars[n % 16];
        n /= 16;
    }

    // 역순 출력
    for (int j = 0; j < i; j++)
    {
        char c = buf[i - 1 - j];
        axlib_write(STDOUT_FD, &c, 1);
    }
}

long read_line(char *buf, size_t size)
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

        str_write("A\n");

        if (ret < 0)
            return ret; // 진짜 에러

        if (ret == 0)
        {
            // axlib_yield();
            continue;
        }

        if (ch == '\r')
        {
            str_write("R");
            break;
        }

        if (ch == '\n')
        {
            str_write("N");
            break;
        }

        buf[used++] = ch;
    }
    str_write("C");

    buf[used] = '\0';
    return (long)used;
}