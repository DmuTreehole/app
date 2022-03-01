   
#include "hi_pwm.h"
#include "hi_gpio.h"
#include "hi_io.h"
#include "hi_time.h"

//-60 ~ 60 稳 -90有的时候不好使
hi_void set_angle(hi_s32 angle)
{
    hi_s32 duty = 1500 - 1000 * angle / 90;
    for (int i = 0 ; i < 10 ; i++)
    {        //舵机初始化
        hi_io_set_func(HI_IO_NAME_GPIO_2,HI_IO_FUNC_GPIO_2_GPIO);
        hi_gpio_set_dir(HI_GPIO_IDX_2,HI_GPIO_DIR_OUT);
        hi_gpio_set_ouput_val(HI_GPIO_IDX_2,HI_GPIO_VALUE1);
        hi_udelay(duty);
        hi_gpio_set_ouput_val(HI_GPIO_IDX_2,HI_GPIO_VALUE0);
        hi_udelay(20000-duty);
    }
}
