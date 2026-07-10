#include <kernel.h>
#include <string.h>

#include "io.h"
#include "defs.h"

void str_write(const char *text)
{
    axlib_write(STDOUT_FD, text, axlib_strlen(text));
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
    if (!buf || size == 0)
        return -1;
    size_t used = 0;

    while (used < size - 1)
    {
        char ch;
        long ret = axlib_read(STDIN_FD, &ch, 1);

        if (ret < 0)
            return ret; // 에러 처리
        if (ret == 0)
            continue; // 데이터 없음, 계속 대기

        if (ch == '\n' || ch == '\r')
            break;

        buf[used++] = ch;
    }

    buf[used] = '\0';
    return (long)used;
}
