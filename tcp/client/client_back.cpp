#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>
#include <unistd.h>

#define SERVER_PORT 8000
#define MAXBUFF 2048

int main()
{
    int sockfd, connectfd;
    struct sockaddr_in servaddr;
    char servip[] = "192.168.199.200";
    char in[1024];
    char buf[MAXBUFF];
    //1.socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd)
    {
        printf("socket create successful!\n");
    }
    else if(sockfd == -1)
    {
        printf("socket create failed! error = %d\n", sockfd);
    }

    //2.connect
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, servip, &servaddr.sin_addr.s_addr);
    servaddr.sin_port = htons(SERVER_PORT);
    connectfd = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if(connectfd == 0)
    {
        printf("socket connect %s successful!\n",
               servip);
    }

    //3.write
    while(1)
    {
        gets(in);
        printf("strlen(in) = %d\n", (int)strlen(in));
        write(sockfd, in, strlen(in));
        //4.read
        int len = read(sockfd, buf, sizeof(buf));
        printf("read from server : %.*s\n", len, buf);
    }
    //5.close
    close(sockfd);
    return 0;
}
