#ifndef __IO_H__
#define __IO_H__

#include <types.h>

// 문자 출력 함수
void str_write(const char *text);

// 숫자 출력 함수
void int_write(int n);

// 16진수 출력 함수
void hex_write(unsigned int n);

static size_t str_len(const char *s);
int shell_str_eq(const char *lhs, const char *rhs);
long read_line(char *buf, size_t size);

#endif