#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <unistd.h>

#define SERVER_PORT 8000
#define MAX_CONNECTION 1024
#define MAXBUFF 1024

int main()
{
    int socketfd, bfd, lfd, connectfd;
    int addrlen, datalen;
    struct sockaddr_in servaddr, clientaddr;
    bzero(&servaddr, sizeof(servaddr));

    char ipaddr[128];
    char buf[MAXBUFF];

    //1.socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketfd == -1)
    {
        printf("socket create error!\n");
    }
    else if(socketfd)
    {
        printf("socket create successful!\n");
    }

    //init socket address
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8000);

    //2.bind
    bfd = bind(socketfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if(bfd == 0)
    {
        printf("socket bind successful!\n");
    }
    else
    {
        printf("socket bind failed! error = %d\n", bfd);
    }

    //3.listen
    lfd = listen(socketfd, MAX_CONNECTION);
    if(lfd == 0)
    {
        printf("socket listen successful!\n");
    }

    while(1)
    {
        //4.accept
        addrlen = sizeof(clientaddr);
        connectfd = accept(socketfd, (struct sockaddr*)&clientaddr, (socklen_t *)&addrlen);
        if(connectfd)
        {
            inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, ipaddr, sizeof(clientaddr));
            printf("client ip %s\t port %d\n",
                   inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, ipaddr, sizeof(clientaddr)),
                   ntohs(clientaddr.sin_port));
            //5.read
            int len = read(connectfd, buf, sizeof(buf));
            printf("read data from client = %s, len = %d\n", buf, len);
            int i = 0;
            while(i < len)
            {
                buf[i] = toupper(buf[i]);
                i++;
            }

            //6.write
            write(connectfd, buf, len);

            //7.close
            if(close(connectfd) == 0)
            {
                printf("client %s has closed!\n", inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, ipaddr, sizeof(clientaddr)));
            }
        }
    }

    close(socketfd);
    return 0;
}
