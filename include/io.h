#ifndef _IO_H_
#define _IO_H_

#include <types.h>

// 문자 출력 함수
void str_write(const char *text);

// 숫자 출력 함수
void int_write(int n);

// 16진수 출력 함수
void hex_write(unsigned int n);

void file_crate(const char *path, int mode, uint32_t size);
void file_open(const char *path, int flag);
void file_close(void);

long read_line(char *buf, size_t size);
uint8_t parse(char *input, char *argv[], int max_args);
#endif