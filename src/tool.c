#include "tool.h"

int file_chg_auth(uint8_t *auth)
{
    // 크기가 4바이트를 만족시키지 못하면 리턴하기

    int ret = 0;

    for (int i = 0; i < 4; i++)
    {
        int digit = auth[i] - '0';

        ret = (ret << 3) | (digit & 0x7);
    }
    return ret;
}