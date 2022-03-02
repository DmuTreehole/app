#ifndef NET
#define NET

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include "lwip/sockets.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include "motor.h"

#define SIZE 128

void UdpServer(unsigned short port)
{
    ssize_t retval = 0;
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); // UDP socket

    struct sockaddr_in clientAddr = {0};          //客户端信息
    socklen_t clientAddrLen = sizeof(clientAddr); // 客户端长度
    struct sockaddr_in serverAddr = {0};          // 服务端信息

    bzero(&clientAddr, clientAddrLen); // 归零
    // 配置服务端信息
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // 端口绑定
    retval = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (retval < 0)
    {
        printf("bind failed, %ld!\r\n %s", retval, strerror(errno));
        goto do_cleanup;
    }
    printf("bind to port %d success!\r\n", port);

    // 接受信息
    char buf[SIZE];
    while (1)
    {
        // 每次清空BUF
        bzero(buf, SIZE);
        retval = recvfrom(sockfd, buf, SIZE, 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (retval < 0)
        {
            printf("recvfrom failed, %ld!\r\n", retval);
        }
        else
        { // 成功就打印出信息
            printf("%s", buf);
            //printf(strcmp("up", buf));
            if (!strcmp("up\n", buf)) // 结束符也要比较
            {
                go_forward(400);
                //printf("前进\n");
            }
            else if (!strcmp("back\n", buf))
            {   go_back(400);
                //printf("后退\n");
            }
            else if (!strcmp("left\n", buf))
            {
                go_turnleft(400);
                //printf("左转\n");
            }
            else if (!strcmp("right\n", buf))
            {
                go_turnright(400);
                //printf("右转");
            }
        }
    }

do_cleanup:
    lwip_close(sockfd);
    return;
}

/*
int main()
{
    UdpServer(7895);
    return 0;
}
*/

#endif