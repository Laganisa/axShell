#ifndef __SHELL_IO_H__
#define __SHELL_IO_H__

#include <types.h>
#include <call.h>

// long read_line(char *buf, size_t size);
uint8_t parse(char *input, char *argv[], int max_args);
#endif