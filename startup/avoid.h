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
    if(leftdistance<=rightdistance){
        //右转
        go_back(400);
        go_turnright(200);
        stop();
    }else{
        //左转
        go_back(400);
        go_turnright(200);
        stop();
    }
    set_angle(0);
    go_forward(200);
}
#endif 


