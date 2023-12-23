#include "comm.hpp"
using namespace std;
//客户端这里只需要写入信息

int main()
{
    int fd=open(FIFO_FILE,O_WRONLY);
    if(fd<0)
    {
        perror("open");
        exit(FIFO_OPEN_ERR);
    }
    //打开成功后就可以进行通信
    cout<<"client opne file done"<<endl;
    string line;
    while(1)
    {
        cout<<"Please Enter@: "<<endl;
        getline(cin,line);
        write(fd,line.c_str(),line.size());
    }
    close(fd);

    return 0;
}

