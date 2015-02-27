#pragma config(Hubs, S1, MatrxRbtcs, none, none, none)
#pragma config(Sensor, S1, , sensorI2CMuxController)
#pragma config(Motor, mtr_Matrix_S1_1, motorD, tmotorMatrix, openLoop, reversed)
#pragma config(Motor, mtr_Matrix_S1_2, motorE, tmotorMatrix, openLoop)
#pragma config(Motor, mtr_Matrix_S1_3, motorF, tmotorMatrix, openLoop, reversed)
#pragma config(Motor, mtr_Matrix_S1_4, motorG, tmotorMatrix, openLoop)
#pragma config(Servo, srvo_Matrix_S1_1, servo1, tServoNone)
#pragma config(Servo, srvo_Matrix_S1_2, servo2, tServoNone)
#pragma config(Servo, srvo_Matrix_S1_3, servo3, tServoNone)
#pragma config(Servo, srvo_Matrix_S1_4, servo4, tServoNone)

#pragma DebuggerWindows("joystickSimple")
#include "JoystickDriver.c"

// Declare variables at the start of the document
int y1,
    y1n,
    y2,
    y2n,
    x1,
    x1n,
    x2,
    x2n,
    lmot,
    rmot;

task main(){
	while(true){
	getJoystickSettings(joystick);

	// Normalize Y values
	y1 = joystick.joy1_y1 * 100;
	y1n = y1 / 128;

	y2 = joystick.joy1_y2 * 100;
	y2n = y2 / 128;

	// Normalize X values
	x1 = joystick.joy1_x1 * 100;
	x1n = x1 / 128;

	x2 = joystick.joy1_x2 * 100;
	x2n = x2 / 128;

	lmot = y2n;
	rmot = y1n;

	// Steering thing
	if(x1n < 0) lmot = y2n + x2n;
	else rmot = y1n - x1n;

	if(!joy1Btn(5)){
		lmot = lmot / 2;
		rmot = rmot / 2;
	}

	if(abs(lmot) > 8){
		motor[motorD] = lmot;
		motor[motorF] = lmot;
	}else{
		motor[motorD] = 0;
		motor[motorF] = 0;
	}

	if(abs(rmot) > 8){
		motor[motorE] = rmot;
		motor[motorG] = rmot;
	}else{
		motor[motorE] = 0;
		motor[motorG] = 0;
	}

	wait1Msec(10);
	}
}
