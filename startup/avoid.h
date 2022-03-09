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
        go_back(200);
        go_turnright(200);
    }else{
        //左转
        go_back(200);
        go_turnright(200);
    }
    set_angle(0);
    go_forward(900);
}
#endif 


