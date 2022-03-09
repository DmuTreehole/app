#ifndef AVOID
#define AVOID
#include"steering.h"
#include"motor.h"
#include"supersound.h"
void avoid(){
    //先停下来
    float leftdistance,rightdistance=0;
    stop()
    set_angle(-60);
    leftdistance=getDistance();
    set_angle(60);
    rightdistance=getDistance();
    if(leftdistance<=rightdistance){
        //右转
        go_back(100);
        go_turnright(300);
    }else{
        //左转
        go_back(100);
        go_turnright(300);
    }
    set_angle(0);
    go_forward(400);
}
#endif 


