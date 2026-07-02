#include <kernel.h>

#define UART0_BASE 0x09000000
#define UART0_DR ((volatile uint32_t *)(UART0_BASE + 0x00))
#define UART0_FR ((volatile uint32_t *)(UART0_BASE + 0x18))
#define UART0_CR ((volatile uint32_t *)(UART0_BASE + 0x30))

void uart_putchar(int8_t c)
{
    // UART_FR 5번 비트: TXFF (보낼 데이터 칸이 꽉 찼는지 확인)
    while (*UART0_FR & (1 << 5))
    {
    }

    *UART0_DR = c;
}

// 문자열 출력
void uart_puts(const int8_t *s)
{
    while (*s)
    {
        uart_putchar(*s++);
    }
}

// 문자 입력 (UART에서 수신 대기)
int8_t uart_getchar(void)
{
    // UART_FR 레지스터 4번 비트: RX FIFO empty
    // 데이터가 올 때까지 대기
    while (*UART0_FR & (1 << 4))
    {
        // UART가 데이터를 기다리는 중
    }
    return *UART0_DR;
}

// 문자열 입력 (Enter까지 받음)
void uart_gets(int8_t *s, int32_t max_len)
{
    int32_t i = 0;
    while (i < max_len - 1)
    {
        int8_t c = uart_getchar();

        // 1. 엔터 처리
        if (c == '\r' || c == '\n')
        {
            uart_putchar('\n');
            break;
        }
        // 2. 백스페이스 처리 (ASCII 8: \b, 127: DEL)
        else if ((c == '\b' || c == 127))
        {
            if (i > 0)
            {
                i--;
                s[i] = '\0';        // 버퍼에서 제거
                uart_puts("\b \b"); // 화면에서 제거
            }
            // i가 0일 때는 아무것도 안 함 (프롬프트 보호)
        }
        // 3. 일반 문자 입력 (에코는 여기서만!)
        else if (c >= 32 && c < 127)
        {
            s[i++] = c;
            uart_putchar(c); // 백스페이스나 엔터가 아닐 때만 화면에 출력
        }
    }
    s[i] = '\0';
}