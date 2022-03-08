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

#define SIZE1 128

int speed = 800;
int isauto = 0;
int direct = 0; // 0 直行 -1 后退 1 左转 2右转
bool isTouched=false;
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
 
void UdpServer(unsigned short port)
{

    int send_length=0;
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
            //如果有避障，发一个包给前端
            if(isTouched==true){
                strcpy(buf,"touched\n");
                send_length=sendto(sockfd, buf, SIZE1, 0, (struct sockaddr *)&clientAddr, clientAddrLen);
                if(send_length<0){
                    printf("发送数据包失败\n");
                }
                printf("已发送数据包\n");
            }
            isTouched=false;//初始化为没有避障的状态
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
	    } else if (!strcmp("auto\n", buf)) {
		printf("自动巡航");	
		while(1) {
		if (getDistance() < 10 ) {
			go_turnleft(2000);
		} else {
		   go_forward(400);
		}
		// 接受指令
	        bzero(buf, SIZE1);
                retval = recvfrom(sockfd, buf, SIZE1, 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
                if (retval < 0)
                {
                    printf("recvfrom failed, %ld!\r\n", retval);
	        } else {
	            stop();
	            break;
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
