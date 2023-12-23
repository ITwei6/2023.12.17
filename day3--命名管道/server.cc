

#include "comm.hpp"
// 服务端创建信道，客户端只需要发送信息即可
// 使用命名管道，就像使用文件一样要

using namespace std;

// 管理管道文件
int main()
{
    int n = mkfifo(FIFO_FILE, MODE);
    if (n == -1) // 创建失败
    {
       
        perror("mkfifo");
        exit(FIFO_CREATE_ERR); // 创建失败就退出
    }

    // 使用管道文件--如何使用呢？就跟文件操作一样使用，打开，写入关闭
    int fd = open(FIFO_FILE, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        exit(FIFO_OPEN_ERR);
    }
    while (1)
    {
        // 读取到一个数组里
        char buffer[1024] = {0};

        int x = read(fd, buffer, sizeof(buffer));
        if (x > 0) // 说明读取成功
        {
            buffer[x] = 0;
            //读取完后，就将客户端发送
            cout << "client say@ " << buffer << endl;
        }
        else if (x == 0) // 说明读取结束，读到末尾
        {
            break;
        }
        else
            break;
    }
    close(fd);

    // 最后不用了，就删除管道文件
    int m = unlink(FIFO_FILE);
    if (m == -1)
    {
        perror("unlink");
        exit(FIFO_DELETE_ERR);
    }

    return 0;
}
