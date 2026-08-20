#include <kernel.h>
#include <string.h>

#include "io.h"
#include "defs.h"
#include "call.h"

// ! 여기 수정 필요
/*
long read_line(char *buf, size_t size)
{
    if (!buf || size == 0)
        return -1;
    size_t used = 0;

    while (used < size - 1)
    {
        char ch;
        long ret = axlib_read(STDIN_FD, &ch, 1, 0);

        if (ret < 0)
            return ret;

        if (ret == 0)
            // 데이터 없음, 계속 대기
            // ? 나중에 양보 함수 만들 예정
            continue;

        if (ch == '\n' || ch == '\r')
            break;

        buf[used++] = ch;
    }

    buf[used] = '\0';
    return (long)used;
}
*/

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
