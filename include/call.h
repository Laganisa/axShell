#ifndef __SHELL_CALL_H__
#define __SHELL_CALL_H__

#include "defs.h"
#include <types.h>
#include <kernel.h>

void file_creat(const char *path, int mode, uint32_t size);
long file_open(const char *path, int flag);
void file_close(int fd);
void str_write(const char *text);
void gen_write(int fd, const char *text);

void kernel_setup(uint8_t *buf, uint8_t rule);
void net_send(uint8_t *data, uint8_t id, uint8_t len, uint16_t type);

#endif