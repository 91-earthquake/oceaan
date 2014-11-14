#pragma config(Sensor, S1, ACCEL, sensorI2CHiTechnicAccel)

#include "AdvancedSensors.c"

//Variabelen
float snelheid;
float afstand;

//Constanten
float G = 9.81;
// 200 komt overeen 1G
float Gsens = 200;
//Alleen snelheid aanpassen als vesnelling > 1 cm/s^2
float accelthreshold = 0.01;
//Alleen afstand aanpassen als snelheid > 1 mm/s
float speedthreshold = 0.001;

//Wordt later aangepast door getAfstand Taak
float nulmeting = 0;

/* Zet de sensor waarde om naar de versnelling in m/s^2 */
float convAccel(int sensor_waarde)
{
	float accel;
	//Bereken de uitwijking tenopzichte van de nulmeting
	int uitwijking = sensor_waarde - nulmeting;
	//zet de waarde om in m/s^2
	accel = (uitwijking / Gsens) * G;
	return accel;
}

/* rijdt vooruit, met gegeven afstand */
void rijdtVooruit(float distance) {
	afstand = 0;
	//Rijden
	motor[motorA] = 50;
	motor[motorB] = 50;
	//Totdat de afstand >= distance
	while (afstand < distance) {
		wait1Msec(10);
	}
	//Afstand verreden
	motor[motorA] = 0;
	motor[motorB] = 0;
}

task getAfstand()
{
	//Initialiseer variabelen
	float deltaTime = 0;
	float prevSpeed = 0;
	float prevDistance = 0;
	float curAccel = 0;

	int x, y, z;

	//TODO doe een aantal nulmetingen

	//Lus om de waarden te meten
	while (true) {
		time1[T1] = 0;
		//Lees de huidige acceleratie uit
		getAccel(ACCEL, x,y,z);
		curAccel = convAccel(x);
		//Alleen snelheid aanpassen als de versnelling groter is dan de threshold
		if (abs(curAccel) > accelthreshold ) {
			prevSpeed = snelheid;
			// m/s = m/s + m/s^2 * s

			/* Bereken de huidige snelheid:
			 * V_huidig = V_begin + a * t
			 */
			snelheid = prevSpeed + curAccel * deltaTime;
		}
		//Alleen de afstand aanpassen als de snelheid groter is dan de threshold
		if (abs(snelheid) > speedthreshold) {
				prevDistance = afstand;
				// m = m + m/s * s

				/* Bereken de afgelegde weg:
				 * x = x_begin + v * t
				 */
				afstand = prevDistance + snelheid * deltaTime;
		}
		//Wacht 5 ms.
		wait1Msec(5);
		//Bereken het verschil in tijd, ten opzcihte van de vorige meting
		deltaTime = ((float)time1[T1]) / 1000;
	}
}



task main()
{
	//"verplichte" code
	afstand = 0;
	snelheid = 0;
	//Evt. ook voor gyrosensor
	wait1Msec(10);

	//Start de taak om de afstand te meten
	startTask(getAfstand);
	//Einde "verplichte" code


	//Voorbeeld code: toont waarden op het scherm
	while(true){
		//Zet de waarden op het scherm
		displayTextLine(1, "Speed: %f", snelheid);
		displayTextLine(2, "Dist.: %f", afstand);

		//Screen refresh van 100 FPS
		wait1Msec(10);
	}

	//Hoe te gebruiken: rijdt 0.5m
	rijdtVooruit(0.5);


}
