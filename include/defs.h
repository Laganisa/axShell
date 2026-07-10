#ifndef __DEFS_H__
#define __DEFS_H__

// 시스템 콜 관련
#define STDIN_FD 0
#define STDOUT_FD 1

//배열 크기
#define BUFFER_SIZE 128
#define CMD_TOKEN_SIZE 8
#define MAX_CMD_TOKEN_LEN 8


enum CMD {
    HELP = 1,
    CLEAR,

};



#endif