#include "unp.h"
#include <time.h>

int main(int argc, char **argv)
{
    int connfd, listenfd;
    char buff[MAXLINE];
    struct sockaddr_in serveraddr;
    time_t ticks;

    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        err_sys("socket error");
    }

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // daytime server
    serveraddr.sin_port = htons(13);

    if(bind(listenfd, (SA*)&serveraddr, sizeof(serveraddr)) < 0)
    {
        err_sys("bind error");
    }

    listen(listenfd, LISTENQ);
    for(;;)
    {
        if((connfd = accept(listenfd, (SA*)NULL, NULL)) < 0)
        {
            err_sys("accept error");
        }

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        if(write(connfd, buff, strlen(buff)) < 0)
        {
            err_sys("write error");
        }
        
        close(connfd);
    }

    exit(0);
}
