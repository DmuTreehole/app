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
#include "ohos_init.h"
#include "cmsis_os2.h"

#define SIZE1 128

int speed = 800;
char buf[SIZE1];
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

static void GetCommend(void *arg) {
    (void)arg;       
    ssize_t retval = 0;
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); // UDP socket
    struct sockaddr_in clientAddr = {0};          //客户端信息
    socklen_t clientAddrLen = sizeof(clientAddr); // 客户端长度
    struct sockaddr_in serverAddr = {0};          // 服务端信息

    bzero(&clientAddr, clientAddrLen); // 归零
    // 配置服务端信息
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7895);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // 端口绑定
    retval = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (retval < 0)
    {
        printf("bind failed, %ld!\r\n %s", retval, strerror(errno));
	return;
    }
   
    printf("信息接受初始化完成");
    while(1) {
        // 每次清空BUF
        bzero(buf, SIZE1);
        retval = recvfrom(sockfd, buf, SIZE1, 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (retval < 0)
        {
            printf("recvfrom failed, %ld!\r\n", retval);
        }
        if (!strcmp("close\n",buf)) break;
     }
}

void Openport(void) {
     //创建线程来监听端口
    osThreadAttr_t attr;
    attr.name = "getcommend";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = 10240;
    attr.priority = osPriorityNormal;
    
    if (osThreadNew(GetCommend, NULL, &attr) == NULL) {
        printf("创建信息接受进程失败\n");
    }
}  




void UdpServer(void)
{
   while (1)
    {
           if (!strcmp("up\n", buf)) // 结束符也要比较
            {
                direct = 0;
                go_forward(speed);
                printf("前进\n");
            } else if (!strcmp("back\n", buf))
            {   
                direct = -1;
                go_back(speed);
                printf("后退\n");
            } else if (!strcmp("left\n", buf))
            {
                direct = 1;
                go_turnleft(speed);
                printf("左转\n");
            } else if (!strcmp("right\n", buf))
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
            } else if (!strcmp("auto\n", buf)) {
                forauto(10);
            }
    }
}

/*
int main()
{
    UdpServer(7895);
    return 0;
}
*/

#endif
