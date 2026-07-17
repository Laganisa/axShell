#include "tool.h"

int file_auth(uint8_t *auth)
{
    int ret = 0;

    for (int i = 0; i < 4; i++)
    {
        int digit = auth[i] - '0';

        ret = (ret << 3) | (digit & 0x7);
    }

    return ret;
}