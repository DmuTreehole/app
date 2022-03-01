#include <stdio.h>
#include <unistd.h>
#include "ohos_init.h"
#include "ohos_types.h"
#include "motor.c"
#include "wifi.c"
#include "net.c"
#include "steering.c"
#include "hi_task.h"
// init PWM初始化
hi_void init(hi_void)
{
	hi_gpio_init();
	//引脚复用
	hi_io_set_func(HI_IO_NAME_GPIO_0, HI_IO_FUNC_GPIO_0_PWM3_OUT); 
    hi_io_set_func(HI_IO_NAME_GPIO_1, HI_IO_FUNC_GPIO_1_PWM4_OUT); 	
	hi_io_set_func(HI_IO_NAME_GPIO_9, HI_IO_FUNC_GPIO_9_PWM0_OUT); 
    hi_io_set_func(HI_IO_NAME_GPIO_10, HI_IO_FUNC_GPIO_10_PWM1_OUT); 
	//初始化pwm
	hi_pwm_init(HI_PWM_PORT_PWM3);
    hi_pwm_init(HI_PWM_PORT_PWM4);
	hi_pwm_init(HI_PWM_PORT_PWM0);
    hi_pwm_init(HI_PWM_PORT_PWM1);
}

void HelloWorld(void)
{
    for(;1==1;)
    {
        printf("0\n");
        set_angle(0);
        hi_sleep(3000);
        printf("-60\n");
        set_angle(-60);
        hi_sleep(3000);
        printf("60\n");
        set_angle(60);
        hi_sleep(3000);
        printf("结束楼\n");
        hi_sleep(10000);
    }
   
}

SYS_RUN(HelloWorld); // BUG不用管 入口程序