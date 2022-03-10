#ifndef AVOID
#define AVOID
#include"steering.h"
#include"motor.h"
#include"supersound.h"
void avoid(void){
    //先停下来
    float leftdistance,rightdistance=0;
    stop();
    set_angle(-60);
    leftdistance=getDistance();
    set_angle(60);
    set_angle(60);
    rightdistance=getDistance();
    go_back(800);
    if(leftdistance<=rightdistance){
        //右转
        go_turnright(1000);
        printf("右转\n");
    }else{
        //左转
        go_turnleft(1000);
        printf("左转\n");
    }
    set_angle(0);
    go_forward(200);
}
#endif 


