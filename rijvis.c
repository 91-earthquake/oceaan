#pragma config(StandardModel, "RVW REMBOT")

// Include libraries
#include "JoystickDriver.c"

// Main task
task main(){
 while(true){
   // Get JoyStick values
   getJoystickSettings(joystick);
   
   // Normalize Y values of the left stick and right stick
   int y1 = joystick.joy1_y1*100;
   int y1n = y1/128;
   
   int y2 = joystick.joy1_y2*100;
   int y2n = y2/128;

   // Normalize X values of the left stick and right stick
   int x1 = joystick.joy1_x1*100;
   int x1n = x1/128;
   
   int x2 = joystick.joy1_x2*100;
   int x2n = x2/128;
   
   
   // Set Y values to variables
   int lmot = y2n;
   int rmot = y1n;
   
   // Controll the steering
   if(x1n < 0){
    lmot = y2n + x2n;
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
   // waarom heet dit potvis????, hoor wel van jullie
   // Send values to the motors
   motor[leftMotor] = -1*lmot;
   motor[rightMotor] = -1*rmot;
   
   // Wait 10 milliseconds
   wait1Msec(10);
  }
 }

// Test comment
