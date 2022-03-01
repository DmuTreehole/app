#include <stdio.h>
#include <unistd.h>
#include "ohos_init.h"
#include "ohos_types.h"
#include "motor.c"
#include "wifi.c"

void HelloWorld(void)
{
    RunHotspot();
    osDelay(60);
}

SYS_RUN(HelloWorld); // BUG不用管 入口程序