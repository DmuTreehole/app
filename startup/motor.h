#ifndef MOTOR
#define MOTOR

#include <stdio.h>
#include "ohos_init.h"
#include "ohos_types.h"
#include "hi_io.h"
#include "hi_pwm.h"
#include "hi_gpio.h"


//pwm_control id:gpio引脚号 val:复用功能 port:PWM端口号 duty:占空比
hi_void pwm_control(hi_io_name gpio,hi_u8 val,hi_pwm_port port,hi_u16 duty)
{
    hi_io_set_func(gpio,val);
    hi_pwm_init(port);
    hi_pwm_set_clock(PWM_CLK_160M);
    hi_pwm_start(port,duty,1500);
}

//gpio_control gpio:gpio引脚号 id:硬件的管脚号 dir:gpio输出方向 gpio_val:gpio输出状态 val:gpio引脚功能
hi_void gpio_control(hi_io_name gpio,hi_gpio_idx id,hi_gpio_dir dir,hi_gpio_value gpio_val,hi_u8 val)
{
    hi_io_set_func(gpio,val);
    hi_gpio_set_dir(id,dir);
    hi_gpio_set_ouput_val(id,gpio_val);
}

//go_forward
hi_void go_forward(hi_u16 speed)
{
    gpio_control(HI_IO_NAME_GPIO_0,HI_GPIO_IDX_0,HI_GPIO_DIR_OUT,HI_GPIO_VALUE1,HI_IO_FUNC_GPIO_0_GPIO);
    pwm_control(HI_IO_NAME_GPIO_1,HI_IO_FUNC_GPIO_1_PWM4_OUT,HI_PWM_PORT_PWM4,speed);
    gpio_control(HI_IO_NAME_GPIO_9,HI_GPIO_IDX_9,HI_GPIO_DIR_OUT,HI_GPIO_VALUE1,HI_IO_FUNC_GPIO_0_GPIO);
    pwm_control(HI_IO_NAME_GPIO_10,HI_IO_FUNC_GPIO_10_PWM1_OUT,HI_PWM_PORT_PWM1,speed);
}

//go_back
hi_void go_back(hi_u16 speed)
{    
    pwm_control(HI_IO_NAME_GPIO_0,HI_IO_FUNC_GPIO_0_PWM3_OUT,HI_PWM_PORT_PWM3,speed);
    gpio_control(HI_IO_NAME_GPIO_1,HI_GPIO_IDX_1,HI_GPIO_DIR_OUT,HI_GPIO_VALUE1,HI_IO_FUNC_GPIO_1_GPIO);
    pwm_control(HI_IO_NAME_GPIO_9,HI_IO_FUNC_GPIO_9_PWM0_OUT,HI_PWM_PORT_PWM0,speed);
    gpio_control(HI_IO_NAME_GPIO_10,HI_GPIO_IDX_10,HI_GPIO_DIR_OUT,HI_GPIO_VALUE1,HI_IO_FUNC_GPIO_10_GPIO);
}

//go_turnright
hi_void go_turnright(hi_u16 speed)
{
    gpio_control(HI_IO_NAME_GPIO_0,HI_GPIO_IDX_0,HI_GPIO_DIR_OUT,HI_GPIO_VALUE1,HI_IO_FUNC_GPIO_0_GPIO);
    pwm_control(HI_IO_NAME_GPIO_1,HI_IO_FUNC_GPIO_1_PWM4_OUT,HI_PWM_PORT_PWM4,speed);
    pwm_control(HI_IO_NAME_GPIO_9,HI_IO_FUNC_GPIO_9_PWM0_OUT,HI_PWM_PORT_PWM0,speed);
    gpio_control(HI_IO_NAME_GPIO_10,HI_GPIO_IDX_10,HI_GPIO_DIR_OUT,HI_GPIO_VALUE0,HI_IO_FUNC_GPIO_10_GPIO);
}

//go_turnleft
hi_void go_turnleft(hi_u16 speed)
{
    pwm_control(HI_IO_NAME_GPIO_0,HI_IO_FUNC_GPIO_0_PWM3_OUT,HI_PWM_PORT_PWM3,speed);
    gpio_control(HI_IO_NAME_GPIO_1,HI_GPIO_IDX_1,HI_GPIO_DIR_OUT,HI_GPIO_VALUE0,HI_IO_FUNC_GPIO_1_GPIO);
    gpio_control(HI_IO_NAME_GPIO_9,HI_GPIO_IDX_9,HI_GPIO_DIR_OUT,HI_GPIO_VALUE1,HI_IO_FUNC_GPIO_9_GPIO);
    pwm_control(HI_IO_NAME_GPIO_10,HI_IO_FUNC_GPIO_10_PWM1_OUT,HI_PWM_PORT_PWM1,speed);

}

//stop
hi_void stop(hi_void)
{
    pwm_control(HI_IO_NAME_GPIO_0,HI_IO_FUNC_GPIO_0_PWM3_OUT,HI_PWM_PORT_PWM3,0);
    gpio_control(HI_IO_NAME_GPIO_1,HI_GPIO_IDX_1,HI_GPIO_DIR_OUT,HI_GPIO_VALUE0,HI_IO_FUNC_GPIO_1_GPIO);
    pwm_control(HI_IO_NAME_GPIO_9,HI_IO_FUNC_GPIO_9_PWM0_OUT,HI_PWM_PORT_PWM0,0);
    gpio_control(HI_IO_NAME_GPIO_10,HI_GPIO_IDX_10,HI_GPIO_DIR_OUT,HI_GPIO_VALUE0,HI_IO_FUNC_GPIO_10_GPIO);
}

#endif 