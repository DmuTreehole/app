#include <stdio.h>
#include <unistd.h>
#include "ohos_init.h"
#include "ohos_types.h"
#include "hi_types_base.h"
#include "hi_io.h"
#include "hi_pwm.h"
#include "hi_gpio.h"

float getDistance(void)
{
    //超声波初始化
    hi_io_set_func(HI_IO_NAME_GPIO_7,HI_IO_FUNC_GPIO_7_GPIO);
    hi_gpio_set_dir(HI_GPIO_IDX_7, HI_GPIO_DIR_OUT);
    hi_gpio_set_ouput_val(HI_GPIO_IDX_7, HI_GPIO_VALUE0);
    hi_io_set_func(HI_IO_NAME_GPIO_8,HI_IO_FUNC_GPIO_8_GPIO);
    hi_gpio_set_dir(HI_GPIO_IDX_8,HI_GPIO_DIR_OUT);
    hi_gpio_set_ouput_val(HI_GPIO_IDX_8,HI_GPIO_VALUE0);
    
    hi_u64 start_time = 0;
    hi_u64 end_time; 
    hi_float distance = 0.0;
    hi_gpio_value val = HI_GPIO_VALUE0;
    int flag =  0;
    //echo口方向
    hi_io_set_func(HI_IO_NAME_GPIO_8,HI_IO_FUNC_GPIO_8_GPIO);
    hi_gpio_set_dir(HI_GPIO_IDX_8,HI_GPIO_DIR_IN);
    //发个脉冲 触发测距
    hi_gpio_set_ouput_val(HI_GPIO_IDX_7,HI_GPIO_VALUE1);
    hi_udelay(20);
    hi_gpio_set_ouput_val(HI_GPIO_IDX_7,HI_GPIO_VALUE0);                      
    printf("初始化完成");
    while(1)
    {
        hi_gpio_get_input_val(HI_GPIO_IDX_8,&val);
        //echo高电平时开始计时
        if((val == HI_GPIO_VALUE1) && (flag == 0)){
            start_time = hi_get_us();
            flag = 1;
            printf("Get Start Time \n");
        }
        //echo低电平时结束计时
        if((val == HI_GPIO_VALUE0) && (flag == 1)){
            end_time = hi_get_us() - start_time;
            start_time = 0;
            printf("Get Over Time \n");
            break;
        }
    }
    distance = end_time * 0.034 / 2;
    printf("distance is %f\r\n",distance);
    return distance;
}