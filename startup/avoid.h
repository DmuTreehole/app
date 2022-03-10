#ifndef AVOID
#define AVOID
#include"steering.h"
#include"motor.h"
#include"supersound.h"
//避障
void avoid(void){
    //先停下来
    float leftdistance=0,rightdistance=0;
    stop();
    set_angle(-60);
    leftdistance=getDistance();
    set_angle(60);
    set_angle(60);
    rightdistance=getDistance();
    if(leftdistance<=rightdistance){
        //右转
        go_turnright(100);
        //printf("右转\n");
    }else{
        //左转
        go_turnleft(100);
        //printf("左转\n");
    }
    set_angle(0);
}
#endif 


