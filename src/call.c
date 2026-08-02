#include "call.h"

void str_write(const char *text)
{
    axlib_write(STDOUT_FD, text, axlib_strlen(text));
}

void gen_write(int fd, const char *text)
{
    axlib_write(fd, text, axlib_strlen(text));
}

void file_creat(const char *path, int mode, uint32_t size)
{
    axlib_file_creat(path, mode, size);
}

long file_open(const char *path, int flag)
{
    return axlib_open(path, flag);
}

void file_close(int fd)
{
    axlib_close(fd);
}

void net_send(uint8_t *data, uint8_t id, uint8_t len, uint16_t type)
{
    axlib_send(data, id, len, type);
}

void kernel_setup(uint8_t *buf, uint8_t rule)
{
    axlib_setup(buf, rule);
}