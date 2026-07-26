#include "tool.h"
#include <string.h>

int file_chg_auth(uint8_t *auth)
{
    // 크기가 4바이트를 만족시키지 못하면 리턴하기
    if (axlib_strlen(auth) != 4)
    {
        return -1;
    }

    int ret = 0;

    for (int i = 0; i < 4; i++)
    {
        int digit = auth[i] - '0';

        ret = (ret << 3) | (digit & 0x7);
    }
    return ret;
}

uint8_t file_chg_flag(uint8_t is_dev, uint8_t is_write, uint8_t is_read, uint8_t is_append)
{
    uint8_t flag = 0;

    // 장치 여부
    if (is_dev != 0)
    {
        flag |= (1 << 0);
    }

    if (is_write != 0)
    {
        flag |= (1 << 1);
    }

    if (is_read != 0)
    {
        flag |= (1 << 2);
    }

    if (is_append != 0)
    {
        flag |= (1 << 3);
    }

    return flag;
}