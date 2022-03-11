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
#include"supersound.h"
#include "motor.h"
#include"steering.h"
#include"avoid.h"
#define SIZE1 128

int speed = 800;
int direct = 0; // 0 直行 -1 后退 1 左转 2右转
void ChangeSpeed(bool as){
    if (!as) {
        speed += 100;
        if (speed % 100 == 1) {
            speed -= 1;
        }
    }else{
        speed -= 100;
        if(speed < 0 ) {
            speed = 1;
        }
    }
    printf("改变速度,当前速度为：%d",speed);
    switch (direct){
    case 0:
        go_forward(speed);
        break;
    case 1:
        go_turnleft(speed);
        break;
    case 2:
        go_turnright(speed);
        break;
    case -1:
        go_back(speed);
        break;
    }
}
//UDP客户端
void UdpClient(const char *host,unsigned short port)
{
    ssize_t send_length=0;//发送包的长度
    char request[]="complete\n";
    int sendfd=socket(AF_INET, SOCK_DGRAM, 0);
    if(sendfd<0){
        printf("创建发送套接字失败\n");
    }
        //配置发送信息
    struct sockaddr_in receiverAddr={0};
    receiverAddr.sin_family=AF_INET;
    receiverAddr.sin_port = htons(port);
    if (inet_pton(AF_INET, host, &receiverAddr.sin_addr) <= 0) { // 将主机IP地址从“点分十进制”字符串 转化为 标准格式（32位整数）
        printf("inet_pton failed!\r\n");
        goto do_cleanup;
    }
    // UDP socket 是 “无连接的” ，因此每次发送都必须先指定目标主机和端口，主机可以是多播地址
    send_length= sendto(sockfd, request, sizeof(request), 0, (struct sockaddr *)&receiverAddr, sizeof(receiverAddr));
    if (send_length < 0) {
        printf("sendto failed!\r\n");
        goto do_cleanup;
    }
    else
    {
        //printf("避障一次\n");
        printf("传送的数据长度为%d,%s\n",send_length,request);
    }
    printf("send UDP message {%s} %ld done!\r\n", request, retval);
do_cleanup:
    printf("do_cleanup...\r\n");
    close(sockfd);
}
//udp服务端
void UdpServer(unsigned short port)
{

    ssize_t retval = 0;//接收包的长度

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); // UDP socket


    struct sockaddr_in clientAddr = {0};          //客户端信息
    socklen_t clientAddrLen = sizeof(clientAddr); // 客户端长度
    struct sockaddr_in serverAddr = {0};          // 服务端信息

    // //开启广播
    // int on =1;
    // int ret=setsockopt(sendfd,SOL_SOCKET,SO_BROADCAST,&on,sizeof(on));
    // if(ret<0){
    //     printf("广播打开失败\n");
    // }


    // 配置服务端信息
    bzero(&clientAddr, clientAddrLen); // 归零
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // 接收端口绑定
    retval = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (retval < 0)
    {
        printf("bind failed, %ld!\r\n %s", retval, strerror(errno));
        goto do_cleanup;
    }
    printf("bind to receive port %d success!\r\n", port);
    // 接受信息
    char buf[SIZE1];
    while (1)
    {
        // 每次清空BUF
        bzero(buf, SIZE1);
        retval = recvfrom(sockfd, buf, SIZE1, 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (retval < 0)
        {
            printf("recvfrom failed, %ld!\r\n", retval);
        }
        else
        { // 成功就打印出信息
            printf("%s", buf);
            if (!strcmp("up\n", buf)) // 结束符也要比较
            {
                direct = 0;
                go_forward(speed);
                printf("前进\n");
            }
            else if (!strcmp("back\n", buf))
            {   
                direct = -1;
                go_back(speed);
                printf("后退\n");
            }
            else if (!strcmp("left\n", buf))
            {
                direct = 1;
                go_turnleft(speed);
                printf("左转\n");
            }
            else if (!strcmp("right\n", buf))
            {
                direct = 2;
                go_turnright(speed);
                printf("右转\n");
            }else if (!strcmp("stop\n", buf))
            {
                stop();
                speed = 400;
                printf("停车\n");
            }else if (!strcmp("speedup\n", buf))
            {
                ChangeSpeed(true);
                printf("加速\n");
            }else if (!strcmp("speeddown\n", buf))
            {
                ChangeSpeed(false);
                printf("减速\n");
            } else if (!strcmp("auto\n", buf)) 
            {
            printf("自动巡航\n");	
            while(1) {
            if (getDistance() < 30 ) 
            {
                avoid();
                bzero(buf, SIZE1);
                UdpClient("192.168.1.2",7856)
            } 
            else 
            {
                //printf("继续前进\n");
                go_forward(800);
            }
            }
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
