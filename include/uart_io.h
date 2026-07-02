#ifndef __UART_IO_H__
#define __UART_IO_H__

#include <kernel.h>

void uart_putchar(int8_t c);
void uart_puts(const int8_t *s);
int8_t uart_getchar(void);
void uart_gets(int8_t *s, int32_t max_len);

#endif