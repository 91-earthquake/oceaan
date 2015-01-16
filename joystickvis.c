#pragma config(Hubs,  S1, MatrxRbtcs, none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_Matrix_S1_1, motorD,        tmotorMatrix, PIDControl, encoder)
#pragma config(Motor,  mtr_Matrix_S1_2, motorE,        tmotorMatrix, PIDControl, encoder)
#pragma config(Motor,  mtr_Matrix_S1_3, motorF,        tmotorMatrix, PIDControl, encoder)
#pragma config(Motor,  mtr_Matrix_S1_4, motorG,        tmotorMatrix, PIDControl, reversed, encoder)
#pragma config(Servo,  srvo_Matrix_S1_1, servo1,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_2, servo2,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_3, servo3,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_4, servo4,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * @author Earthquake
 */

#pragma DebuggerWindows("joystickSimple")
#include "JoystickDriver.c"

task main(){
	while(true){
		// Get the joystick settings
		getJoystickSettings(joystick);

		// Set a value to define a 'dead area' on the joystick
		int treshold = 8;

		// Define the y1, x1, y2, x2 variables
		int y1,
		    x1,
		    y2,
		    x2;

		// Define the variables for the power and the steering,
		// And the left and the right motor, but engine sounds better
		int power,
		    steering,
		    left_engine,
		    right_engine;


		// Only set the values to y1 if the value exeeds the treshold
		if (abs(joystick.joy1_y1) > treshold) y1 = joystick.joy1_y1;
		else y1 = 0;

		// Only set the values to x1 if the value exeeds the treshold
		if (abs(joystick.joy1_x1) > treshold) x1 = joystick.joy1_x1;
		else x1 = 0;

		// Only set the values to y2 if the value exeeds the treshold
		if (abs(joystick.joy1_y2) > treshold) y2 = joystick.joy1_y2;
		else y2 = 0;

		// Only set the values to x2 if the value exeeds the treshold
		if (abs(joystick.joy1_x2) > treshold) x2 = joystick.joy1_x2;
		else x2 = 0;

		// Normalize the values
		y2 = (y2 * 100) / 128;
		x1 = (x1 * 100) / 128;

		// Assign the y2 variable to the power variable
		power = -y2;

		// Assign the x1 variable to the steering variable
		steering = x1;

		// Only divide by 2 if the boost is not pressed
		if(!joy1Btn(8)){
			power = power / 2.5;
			steering = steering / 2.5;
		}else{}
		

		// Assign the power to the variables
		right_engine = power - steering;
		left_engine  = power + steering;

		// Assign the calculated values to the engines
		motor[motorF] = right_engine;
		motor[motorG] = left_engine;

		wait1Msec(10);
	}
}