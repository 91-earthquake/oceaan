#pragma config(StandardModel, "RVW REMBOT")
#include "JoystickDriver.c"

task main(){

 while(true){
   getJoystickSettings(joystick);

   int y1 = joystick.joy1_y1*100;
   int y1n = y1/128;

   int x1 = joystick.joy1_x1*100;
   int x1n = x1/128;

   int lmot = y1n;
   int rmot = y1n;

   if(x1n < 0){
    lmot = y1n + x1n;
   }else{
   	rmot = y1n - x1n;
   }

   if(joy1Btn(6)){
     motor[motorA] = 100;
   }else{
   	motor[motorA] = -100;
   }

   motor[leftMotor] = lmot;
   motor[rightMotor] = rmot;

   wait1Msec(10);
  }
 }
