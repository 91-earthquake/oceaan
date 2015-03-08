#pragma config(Hubs, S1, MatrxRbtcs, none, none, none)
#pragma config(Hubs, S2, MatrxRbtcs, none, none, none)
#pragma config(Sensor, S1, , sensorI2CMuxController)
#pragma config(Motor, mtr_Matrix_S1_1, motorA, tmotorMatrix, PIDControl, encoder)
#pragma config(Motor, mtr_Matrix_S1_2, motorB, tmotorMatrix, PIDControl, reversed, encoder)
#pragma config(Motor, mtr_Matrix_S1_3, motorC, tmotorMatrix, PIDControl, encoder)
#pragma config(Motor, mtr_Matrix_S1_4, motorD, tmotorMatrix, PIDControl, encoder)
#pragma config(Motor, mtr_Matrix_S2_1, motorE, tmotorMatrix, PIDControl, reversed, encoder)
#pragma config(Motor, mtr_Matrix_S2_2, motorF, tmotorMatrix, PIDControl, encoder)
#pragma config(Motor, mtr_Matrix_S2_3, motorG, tmotorMatrix, PIDControl, reversed, encoder)
#pragma config(Motor, mtr_Matrix_S2_4, motorH, tmotorMatrix, PIDControl, encoder)
#pragma config(Servo, srvo_Matrix_S1_1, servo1, tServoNone)
#pragma config(Servo, srvo_Matrix_S1_2, servo2, tServoNone)
#pragma config(Servo, srvo_Matrix_S1_3, servo3, tServoNone)
#pragma config(Servo, srvo_Matrix_S1_4, servo4, tServoNone)
#pragma config(Servo, srvo_Matrix_S2_1, servo5, tServoNone)
#pragma config(Servo, srvo_Matrix_S2_2, servo6, tServoNone)
#pragma config(Servo, srvo_Matrix_S2_3, servo7, tServoNone)
#pragma config(Servo, srvo_Matrix_S2_4, servo8, tServoNone)

/**
 * @author   Earthquake
 * @link     https://github.com/91-earthquake/oceaan/blob/master/joystickvis.c
 */

// Open a the joystick debugger window
// As soon as the program is run
#pragma DebuggerWindows("joystickSimple")

// Include the joystick driver
#include "JoystickDriver.c"

task main(){
	        /////////
	       // tmp //
	      /////////

	      // A temporary variable to switch the servo's
	bool  switching = false,

	      // Another temporary variable
	      releasebtn = false,
	      


	        ////////////
	       // Config //
	      ////////////

	      // Reverse the steering, if you turn your joystick right,
	      // and your robot turns left, set to true.
	bool  reverse_steering = false;

	      // Set a value to define a 'Dead zone' on the joystick
	      // Can be modified, but 5 should be allright
	int   treshold = 8,

	      // The power for the lift engines
	      liftpower = 100,

	      // Define the boost button
	      // Make sure to add one
	      btn_boost = 6,

	      // Define the servo button
	      // Make sure to add one
	      btn_servo = 8,

	      // The lift up button
	      btn_liftup = 2,

	      // The lift down button
	      btn_liftdown = 3,

	      // The amount of milliseconds to wait
	      // At the end of the loop
	      loop_delay = 10,

	      // The value of the limiter
	      // If the power button isn't pressed,
	      // The power will be divided by this
	      limiter = 2,

	      // The steering sensitivity,
	      // the value will be divided by this
	      steer_sensitivity = 2;

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
	
	// Reset the servo's in use
	// servo[servo1] = 0;
	// servo[servo2] = 0;
	// servo[servo3] = 0;
	// servo[servo4] = 0;
	servo[servo5] = 0;
	// servo[servo6] = 0;
	// servo[servo7] = 0;
	// servo[servo8] = 0;

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
		power = y2;

		// Assign the x1 variable to the steering variable
		steering = x1;

		// Divide the steering variable by the factor given in steer_sensitivity
		steering = steering / steer_sensitivity;

		// Only divide the power and the steering
		// by boost if the boost is not pressed
		if(!joy1Btn(btn_boost)){
			power = power / limiter;
			steering = steering / limiter;
		}

		// Assign the power to the variables
		// But first check the reverse_steering bool status
		if(reverse_steering){
			right_engine = power + steering;
			left_engine  = power - steering;
		}else{
			right_engine = power - steering;
			left_engine  = power + steering;
		}
		

		// Assign the calculated values to the engines
		motor[motorE] = left_engine;
		motor[motorF] = right_engine;
		motor[motorG] = left_engine;
		motor[motorH] = right_engine;

		// Control the servo's
		if(joy1Btn(btn_servo) && releasebtn){
			if(switching){
				switching = false;
				servo[servo1] = 250;
			}else{
				switching = true;
				servo[servo1] = 0;
			}
			releasebtn = false;
		}
		if(!joy1Btn(btn_servo) && !releasebtn) releasebtn = true;

		// Control the lift
		// If the liftup button is pressed
		if(joy1Btn(btn_liftup)){
			motor[motorA] = liftpower;
			motor[motorB] = liftpower;
		// Else, if the liftdown button is pressed
		}else if(joy1Btn(btn_liftdown)){
			motor[motorA] = -liftpower;
			motor[motorB] = -liftpower;
		// If nothing is pressed, set engines to zero
		}else{
			motor[motorA] = 0;
			motor[motorB] = 0;
		}

		// Wait the amount of milliseconds given above
		wait1Msec(loop_delay);
	}
}
