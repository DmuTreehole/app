#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "lwip/sockets.h"

static char message[128] = "";
char* UdpServerTest(unsigned short port)
{
    ssize_t retval = 0;
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); // UDP socket

    struct sockaddr_in clientAddr = {0};
    socklen_t clientAddrLen = sizeof(clientAddr);
    struct sockaddr_in serverAddr = {0};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    retval = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (retval < 0) {
        printf("bind failed, %ld!\r\n", retval);
        goto do_cleanup;
    }
    printf("bind to port %d success!\r\n", port);

    retval = recvfrom(sockfd, message, sizeof(message), 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (retval < 0) {
        printf("recvfrom failed, %ld!\r\n", retval);
    }
do_cleanup:
    lwip_close(sockfd);
    return message;
}
