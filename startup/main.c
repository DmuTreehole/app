#include <stdio.h>
#include <unistd.h>
#include "ohos_init.h"
#include "ohos_types.h"
#include "motor.h"
#include "wifi.h"
#include "net.h"
#include "steering.h"
#include "hi_task.h"
#include "connecter.h"
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

void Move(void) {
	// RunHotspot();
	WifiConnectDemo();	//STA模式
  	UdpServer(7895);    
 }

SYS_RUN(Move); // BUG不用管 入口程序
