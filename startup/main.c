#include <stdio.h>
#include <unistd.h>
#include "ohos_init.h"
#include "ohos_types.h"
#include "motor.c"
#include "wifi.c"
void HelloWorld(void)
{
    printf("Now Go.\n");
    go_forward(300);
}


SYS_RUN(HelloWorld); // BUG不用管 入口程序