
#pragma config(Sensor, S2,     GyroSensor,     sensorI2CHiTechnicGyro)
#pragma config(Motor,  motorC,          MotorDrive1,   tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          MotorDrive2,   tmotorNXT, PIDControl, encoder)

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


float currHoek;
int offset = 598;

task getHoek () {
	float delTime = 0;    //delta time
	float prevHoek = 0;   //vorige hoek
	float curRate = 0;    //huidige snelheid
	
  

while(true) {

time1[T1] = 0;
    //De huidige snelheid van de hoek meten
    curRate = SensorValue[GyroSensor] - offset;
    //Als de huidige snelheid groter is dan 3 graden / seconde
    if (abs(curRate) > 3) {
    	//De vorige hoek wordt de huidige hoek
      prevHoek = currHoek;
      //De nieuwe hoek wordt de vorige hoek + de snelheid (currate) * de tijd
      currHoek = prevHoek + curRate * delTime;
      //Zorg dat de hoek tussen 0 en 360 gragen blijft
      if (currHoek > 360) currHoek -= 360;
      else if (currHoek < 0) currHoek += 360;
    }
    //Wachten 5 ms
    wait1Msec(5);
    //Bereken het verschil in tijd, ten opzichte van de vorige meting
    delTime = ((float)time1[T1]) / 1000;
  }


}


	task main()
{
	startTask(getHoek);
	
	//rij 3 seconden vooruit

			motor[MotorDrive1] = 50;
			motor[MotorDrive2] = 50;
			wait1Msec(3000);

			//zet dan de motoren voor 3 seconden uit
		  motor[MotorDrive1] = 0;
		  motor[MotorDrive2] = 0;
		  wait1Msec(3000);
		  
		  int starthoek = currHoek;
		  
		  wait1Msec(10);
		  
		while(true)
		{


		  //als de gemeten hoek groter dan 0 en kleiner dan 90 graden is, zet de ene motor aan en de andere uit

		if( currHoek > (starthoek + 90) % 360  )
		{

		motor[MotorDrive1] = 50;
		motor[MotorDrive2] = 0;

		} //als de gemeten waard gelijk is aan 90 graden, zet de motoren dan uit
		else {
			motor[MotorDrive1] = 0;
			motor[MotorDrive2] = 0;
		}

		wait1Msec(10);

     	 }
 }
