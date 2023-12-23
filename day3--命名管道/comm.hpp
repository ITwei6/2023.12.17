#pragma once

#include <iostream>
#include <cerrno>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <cstdlib>
#define FIFO_FILE "./myfifo" // 在当前目录下创建命名管道myfifo
#define MODE 0664

enum
{
    FIFO_CREATE_ERR = 1,
    FIFO_OPEN_ERR,
    FIFO_DELETE_ERR
};

class Init
{
    Init()
    {
        int n = mkfifo(FIFO_FILE, MODE);
        if (n == -1) // 创建失败
        {

            perror("mkfifo");
            exit(FIFO_CREATE_ERR); // 创建失败就退出
        }
    }
    ~Init()
    {
        // 最后不用了，就删除管道文件
        int m = unlink(FIFO_FILE);
        if (m == -1)
        {
            perror("unlink");
            exit(FIFO_DELETE_ERR);
        }
    }
};