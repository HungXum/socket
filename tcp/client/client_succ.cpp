#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#define SERVER_PORT 8000
#define MAXLINE 4096
int main(int argc, char *argv[])
{
    struct sockaddr_in serveraddr;
    int sockfd, confd, len;
    char ipstr[] = "192.168.199.200";
    char buf[MAXLINE];
    if (argc < 2) {
        printf("./client str\n");
        exit(1);
    }
    //1.创建一个socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd)
    {
        printf("socket create sucessful!\n");
    }
    else if(sockfd == -1)
    {
        printf("socket create failed! error = %d\n", sockfd);
    }
    //2.初始化服务器地址
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    //"192.168.6.254"
    inet_pton(AF_INET, ipstr, &serveraddr.sin_addr.s_addr);
    serveraddr.sin_port  = htons(SERVER_PORT);
    //3.链接服务器
    confd = connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if(confd == 0)
    {
        printf("connect server successful!\n");
    }
    else
    {
        printf("connect server %d failed! error = \n", confd);
    }

    //4.请求服务器处理数据
    write(sockfd, argv[1], strlen(argv[1]));
    len = read(sockfd, buf, sizeof(buf));
    printf("rev data from server = %.*s\n", len, buf);

    //5.关闭socket
    close(sockfd);
    return 0;
}
