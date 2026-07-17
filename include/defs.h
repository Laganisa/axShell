#ifndef _DEFS_H_
#define _DEFS_H_

// 시스템 콜 관련
#define STDIN_FD 0
#define STDOUT_FD 1
#define STDOUT_ERR 2

// 배열 크기
#define BUFFER_SIZE 128
#define CMD_TOKEN_SIZE 8
#define MAX_CMD_TOKEN_LEN 8

// 파일 플레그
enum FILE_FLAGS
{
    READ_ONLY = 1,
    READ_WRITE
};

enum CMD
{
    HELP = 1,
    CLEAR,

};

#endif