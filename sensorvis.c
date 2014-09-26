#pragma config(Sensor, S4, lightsensor, sensorLightActive)

task main()
{
	wait1Msec(50);
	while(true) {
		//Wat moet altijd gebeuren?
		motor[motorB] = 50;
		motor[motorC] = 50;

		//Speciale situatie (lichtsensor is donker)
		if (SensorValue(lightSensor) < 45) {
			//Actie die dan moet gebeuren (motoren uit)
			motor[motorB] = 0;
			motor[motorC] = 0;
		}

		//Robot doet zijn ding
		wait1Msec(10);

	}
}
