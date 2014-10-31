#pragma config(Hubs,  S1, MatrxRbtcs, none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     seeker,         sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_Matrix_S1_1, motorD,        tmotorMatrix, PIDControl, encoder)
#pragma config(Motor,  mtr_Matrix_S1_2, motorE,        tmotorMatrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_Matrix_S1_3, motorF,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_4, motorG,        tmotorMatrix, openLoop)
#pragma config(Servo,  srvo_Matrix_S1_1, servo1,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_2, servo2,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_3, servo3,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_4, servo4,               tServoNone)

//Sensor gevoeligheid
int sens = 15;

task main()
{
	playImmediateTone(1000, 1);
  wait1Msec(10);
	//Variabelen declareren
	int seeker_value = 0;
	int direction = 0;

	while(true)
	{
		//Lees de sensor uit
		seeker_value = SensorValue[seeker];
		//Als ik niets zie, rechtuit rijden
		if(seeker_value == 0) {
			seeker_value = 5;
		}
		//Direction aanpassen
		direction = seeker_value - 5;

		//Draaien
		motor[motorD] = 50 + (direction * -1 * sens);
		motor[motorE] = 50 + (direction * sens);
		
	}
}
