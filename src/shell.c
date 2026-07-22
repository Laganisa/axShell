#include <kernel.h>
#include <string.h>

#include "shell.h"
#include "io.h"
#include "defs.h"

void show_help(void)
{
    str_write("");
}

// 나중에 바꿀 예정
static int execute(const char *buffer)
{

    if (axlib_strcmp(buffer, "help") == 0)
    {
        return HELP;
    }
    if (axlib_strcmp(buffer, "clear") == 0)
    {
        return CLEAR;
    }

    str_write("unknown command: ");
    str_write(buffer);
    str_write("\n");
}

int main(void)
{
    debug_main();
    return 0;
}

#pragma region test

/*
    아직 파일 디스크럽터 함수를 만들기 전
    나중에 디스크럽터 테이블을 만들고 난 뒤 사용법이 수정될 예정
*/

// 파일 생성 함수
void foo_file_creat(void)
{
    // 파일 생성
    // 파일 이름, 파일 권한
    // ! 주의 파일 권한 함수에 꼭 4바이트 숫자 값을 넣어야함
    // 파일 크기 B 기준
    file_creat("test", file_chg_auth("0777"), 4096);
}

// 파일 쓰기 함수
void foo_file_write(void)
{
    // 파일을 열기
    // 파일 이름, 방식
    file_open("test", FILE_READ_WRITE);

    // 파일을 열었으니
    // 파일 내부에 쓰임
    str_write("hello world!");

    // 파일을 닫기
    file_close();
}

// 파일 읽기 함수
// ! 아직 read_line함수를 테스트 하지 않음
void foo_file_read(void)
{
    file_open("test", FILE_READ_WRITE);

    char ch[2];

    axlib_read(STDIN_FD, &ch, 1);
    ch[1] = '\0'; // 문자 출력을 위해 널 문자 넣어주기

    file_close();
}

#pragma endregion

void debug_main(void)
{
    str_write("debug shell main\n");

    str_write("\ninf loop\n");
    while (1)
    {
        ;
    }
}

void shell_main(void)
{

    while (1)
    {
        str_write("user_");

        char buffer[MAX_CMD_TOKEN_LEN] = {
            0,
        };

        char *arvg[MAX_CMD_TOKEN_LEN];
        read_line(buffer, BUFFER_SIZE);
        uint8_t token_len = parse(buffer, arvg, MAX_CMD_TOKEN_LEN);

        if (axlib_strcmp(buffer, "exit") == 0)
        {
            break;
        }
        execute(buffer);
        switch (execute(buffer))
        {
        case HELP:
            str_write("");
            break;
        case CLEAR:
            str_write("\033[2J\033[H");
            break;
        default:
            str_write("unknown command: ");
            str_write(buffer);
            str_write("\n");
            break;
        }
    }
}