#ifndef __TOOL_H__
#define __TOOL_H__

#include <kernel.h>
#include <types.h>

int file_chg_auth(uint8_t *auth);
uint8_t file_chg_flag(uint8_t is_dev, uint8_t is_write, uint8_t is_read, uint8_t is_append);

#endif