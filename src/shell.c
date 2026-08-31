#include <kernel.h>
#include <string.h>

#include "shell.h"
#include "io.h"
#include "defs.h"
#include <call.h>

void show_help(void)
{
    write(STDIO, "%s", "");
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

    write(STDIO, "%s", "unknown command: ");
    write(STDIO, "%s", buffer);
    write(STDIO, "%s", "\n");
}

int main(void)
{
    debug_main();
    return 0;
}

#pragma region foo

void foo_file()
{
    file_creat("test", "0777", 4096);

    int fd = file_open("test", 'u', 0);

    write(fd, "%s", "hello world!");

    write(STDIO, "%s", "hello hi\n");

    char ch[2];

    axlib_read(fd, &ch, 1, 0);
    ch[1] = '\0'; // 문자 출력을 위해 널 문자 넣어주기

    write(STDIO, "%s", ch);

    file_close(fd);
}

void foo_net()
{
    // 전송하는거
    // 문자 인덱스 길이 ip 값
    net_send("hi", 0, 2, 7000);
}

#pragma endregion

void debug_main(void)
{
    write(STDIO, "%s", "debug shell main\n");

    char *mem = "hi";

    axlib_ipc_send(mem, 2, 2);
    write(STDIO, "%s", "mem send\n");
    write(STDIO, "%s", "\nshell inf loop\n");
    while (1)
    {
        ;
    }
}

void shell_main(void)
{

    while (1)
    {
        write(STDIO, "%s", "user_");

        char buffer[MAX_CMD_TOKEN_LEN] = {
            0,
        };

        char *arvg[MAX_CMD_TOKEN_LEN];

        read(0, buffer, BUFFER_SIZE);

        uint8_t token_len = parse(buffer, arvg, MAX_CMD_TOKEN_LEN);

        if (axlib_strcmp(buffer, "exit") == 0)
        {
            break;
        }
        execute(buffer);
        switch (execute(buffer))
        {
        case HELP:
            write(STDIO, "%s", "");
            break;
        case CLEAR:
            write(STDIO, "%s", "\033[2J\033[H");
            break;
        default:
            write(STDIO, "%s", "unknown command: ");
            write(STDIO, "%s", buffer);
            write(STDIO, "%s", "\n");
            break;
        }
    }
}

void shell_skeleton()
{
    /*
        부팅 로그
        일단 간단한 글자 출력
    */

    while (1)
    {
        // 일단 setup용 처리를 먼저 하기

        /*
            현재 자신의 위치를 말하는 로직
            즉 스택에 자신의 위치를 넣은뒤
            순차적으로 순회하며 출력하기
        */

        /*
            명령을 입력받고 문자열을
            파싱한 다음에 분기하기
        */

        // 수 많은 if 문...

        /*
            프로세스 관련된 명령들
            1. 프로세스 생성
            2. 프로세스 삭제
            3. 프로세스 권한 변경
            4. 프로세스 상태 변경
        */

        /*
            파일 관련된 명령들
            1. 파일 생성
            2. 파일 삭제
            3. 파일 권한 변경
        */

        /*
            네트워크 관련한 명령들
            ! 나중에 만들거 ! 아직 미정
            브릿지가 만들어지지 않음
        */

        /*
            기타 명령들
        */
    }
}