#include <kernel.h>
#include <string.h>

#include "io.h"
#include "defs.h"

void str_write(const char *text)
{
    axlib_write(STDOUT_FD, text, axlib_strlen(text));
}

void file_crate(const char *path, int mode, uint32_t size)
{
    axlib_creat(path, mode, size);
}

void file_open(const char *path, int flag)
{
    axlib_open(path, flag);
}

void file_close(void)
{
    axlib_close(STDOUT_FD);
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

// ! 여기 수정 필요
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
            return ret;

        if (ret == 0)
            continue; // 데이터 없음, 계속 대기

        if (ch == '\n' || ch == '\r')
            break;

        buf[used++] = ch;
    }

    buf[used] = '\0';
    return (long)used;
}

uint8_t parse(char *input, char *argv[], int max_args)
{
    uint8_t i = 0;
    uint8_t argc = 0;
    while (input[i] != '\0')
    {
        // 공백 넘기기
        if (input[i] == ' ')
        {
            i++;
            continue;
        }
        // NULL확인시 종료
        if (input[i] == '\0')
        {
            break;
        }
        argv[argc++] = &input[i]; // 문자열 시작 주소 입력

        if (argc >= max_args)
        {
            break;
        }
        // 문자열 마지막 확인
        while (input[i] != ' ' && input[i] != '\0')
        {
            i++;
        }
        // 공백을 NULL로 변환
        if (input[i] == ' ')
        {
            input[i] = '\0';
            i++;
        }
    }
    return argc; // 토큰 개수 반환
}
