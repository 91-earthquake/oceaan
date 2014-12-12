#pragma config(Hubs,  S1, MatrxRbtcs, none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_Matrix_S1_1, motorD,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_2, motorE,        tmotorMatrix, openLoop, reversed)
#pragma config(Motor,  mtr_Matrix_S1_3, motorF,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_4, motorG,        tmotorMatrix, openLoop)
#pragma config(Servo,  srvo_Matrix_S1_1, servo1,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_2, servo2,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_3, servo3,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_4, servo4,               tServoNone)

#pragma DebuggerWindows("joystickSimple")
#include "JoystickDriver.c"

task main(){
	while(true){
		 		getJoystickSettings(joystick);

		 		// Normalize Y values
		 		int y1 = joystick.joy1_y1*100;
		 		int y1n = y1/128;

		 		int y2 = joystick.joy1_y2*100;
  			int y2n = y2/128;

  			// Normalize X values
  			int x1 = joystick.joy1_x1*100;
   			int x1n = x1/128;

   			int x2 = joystick.joy1_x2*100;
  	 		int x2n = x2/128;

  	 		//programma van Sibren!

  	 		int lmot = y2n;
	   		int rmot = y1n;

	   		// Steering thing
   			if(x1n < 0) lmot = y2n + x2n;
			  else rmot = y1n - x1n;

  	 		if(!joy1Btn(5)){
	  	 		lmot = lmot/2;
	   			rmot = rmot/2;
	   		}



				motor[motorD] = lmot;
				motor[motorE] = rmot;

				wait1Msec(10);
		}
}
