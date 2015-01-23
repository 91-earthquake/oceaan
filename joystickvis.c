#pragma config(Hubs,  S1, MatrxRbtcs, none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_Matrix_S1_1, motorD,        tmotorMatrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_Matrix_S1_2, motorE,        tmotorMatrix, PIDControl, encoder)
#pragma config(Motor,  mtr_Matrix_S1_3, motorF,        tmotorMatrix, PIDControl, encoder)
#pragma config(Motor,  mtr_Matrix_S1_4, motorG,        tmotorMatrix, PIDControl, encoder)
#pragma config(Servo,  srvo_Matrix_S1_1, servo1,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_2, servo2,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_3, servo3,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_4, servo4,               tServoNone)

/**
 * @version  1.1
 * @author   Earthquake
 * @license  Apache License
 * @link     https://github.com/91-earthquake/oceaan/blob/master/joystickvis.c
 */

// Open a the joystick debugger window
// As soon as the program is run
#pragma DebuggerWindows("joystickSimple")

// Include the joystick driver
#include "JoystickDriver.c"

task main(){

bool  switching;


      // The following variables are config variables:
      // Set a value to define a 'Dead zone' on the joystick
      // Can be modified, but 5 should be allright
int   treshold = 8,

      // Define the boost button
			// Make sure to add one
      boost_button = 12,
      
      // Define the servo_button
      // Make sure to add one
      servo_button = 6,
      
      // The amount of milliseconds to wait
      // At the end of the loop
      loop_delay = 10;

	  	// The steering sensitivity, it's a factor
      // So the value will be multiplied by this
float steer_sensitivity = 0.8,
    
      // The value of the limiter
      // If the power button isn't pressed,
      // The power will be divided by this
      limiter = 2.5;

      // Define the y1, x1, y2, x2 variables
int   y1,
      x1,
      y2,
      x2;

      // Define the variables for the power and the steering,
      // And the left and the right motor, but engine sounds better
int   power,
      steering,
      left_engine,
      right_engine;
      
// Reset the servo's
servo[servo1] = 0;
servo[servo2] = 0;

while(true){
		// Get the joystick settings
		getJoystickSettings(joystick);
		
		// Define the 'Dead Zones'
		// Only set the values if the value exeeds the treshold
		if (abs(joystick.joy1_y1) > treshold) y1 = joystick.joy1_y1;
		else y1 = 0;

		if (abs(joystick.joy1_x1) > treshold) x1 = joystick.joy1_x1;
		else x1 = 0;

		if (abs(joystick.joy1_y2) > treshold) y2 = joystick.joy1_y2;
		else y2 = 0;
		
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
		if(!joy1Btn(boost_button)){
			power = power / limiter;
			steering = steering / limiter;
		}
	
		// Multiply the steering variable by the given factor
		// In the variable steer_sensitivity
		steering = steering * steer_sensitivity;
		
		
		// Assign the power to the variables
		right_engine = power - steering;
		left_engine  = power + steering;

		// Assign the calculated values to the engines
		motor[motorD] = right_engine;
		motor[motorF] = left_engine;
		
		// Controll the servo's
		if(joy1Btn(servo_button)){
			if(switching){
				switching = false;
				servo[servo1] = 0;
			}else{
				switching = true;
				servo[servo1] = 200;
			}
			wait1Msec(5);
		}
		
		
		
		// Wait the amount of milliseconds given above
		// So the loop runs 100 times per second
		wait1Msec(loop_delay);
	}
}
