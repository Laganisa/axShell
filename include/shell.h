#ifndef axSHELL_SHELL_H
#define axSHELL_SHELL_H

#include <stddef.h>

#define SHELL_CMD_BUFFER_SIZE 64

int shell_main(void);
void shell_write(const char *text);
int shell_str_eq(const char *lhs, const char *rhs);

#endif
