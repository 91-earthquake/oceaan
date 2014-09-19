#pragma config(StandardModel, "RVW REMBOT")

// Include libraries
#include "JoystickDriver.c"

// Main task
task main(){
 while(true){
   // Get JoyStick values
   getJoystickSettings(joystick);
   
   // Normalize Y values of the left stick
   int y1 = joystick.joy1_y1*100;
   int y1n = y1/128;

   // Normalize X values of the left stick
   int x1 = joystick.joy1_x1*100;
   int x1n = x1/128;
   
   // Set Y values to variables
   int lmot = y1n;
   int rmot = y1n;
   
   // Controll the steering
   if(x1n < 0){
    lmot = y1n + x1n;
   }else{
   	rmot = y1n - x1n;
   }
   
   /*
   This part is for the virtual robot with an arm, not for the physical robot
   if(joy1Btn(6)){
     motor[motorA] = 100;
   }else{
   	motor[motorA] = -100;
   }
   */
   
   // Send values to the motors
   motor[leftMotor] = lmot;
   motor[rightMotor] = rmot;
   
   // Wait 10 milliseconds
   wait1Msec(10);
  }
 }

// Test comment
