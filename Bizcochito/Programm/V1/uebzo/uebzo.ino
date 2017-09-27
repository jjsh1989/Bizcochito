/*
Name:			uebzo.ino
Darstellung:	V.: 1.0.0
Beschreibung:	brazo robotico controlado por servomotores Automatischer-/ Handarbeitfunktion mit Taster und ein Poti
Author:			Julio JSH und Alberto GA
*/

// Biblothek
#include <Servo.h>

// Ein-/ Ausgängen bei Arduino
	// Digital
#define Selektor      11
#define Start		  13
#define TasterServo0   2
#define TasterServo1   4
#define TasterServo2   7
#define TasterServo3   8
#define TasterServo4  12
	//Analog
#define Poti		  A0

// Servos
Servo Servo0;
Servo Servo1;
Servo Servo2;
Servo Servo3;
Servo Servo4;

// Variablen
byte Zunstand;
byte Schritt = 0;
byte Var[6];
byte Grad[5];

//Variablem bei dem Taster
/*
Funktion[0] und LetzterFunktion[0] "Start"
Funktion[1] und LetzterFunktion[1] "Rutsche"
Funktion[2] und LetzterFunktion[2] "Drehgelenk"
Funktion[3] und LetzterFunktion[3] "Vorzurück"
Funktion[4] und LetzterFunktion[4] "Abheben"
Funktion[5] und LetzterFunktion[5] "Klammer"
*/
byte Funktion[6];
byte LetzterFunktion[6];

void setup() {

	Serial.begin(9600);
	// Ausgängen bei Servos
	Servo0.attach(3);     // Pin 3 PWM Arduino
	Servo1.attach(5);     // Pin 5 PWM Arduino
	Servo2.attach(6);     // Pin 6 PWM Arduino
	Servo3.attach(9);     // Pin 9 PWM Arduino
	Servo4.attach(10);      // Pin 10 PWM Arduino

	// Einstellung bei Pin
	pinMode(Selektor, INPUT);
	pinMode(Start, INPUT);
	pinMode(Funktion[1], INPUT);
	pinMode(Funktion[2], INPUT);
	pinMode(Funktion[3], INPUT);
	pinMode(Funktion[4], INPUT);
	pinMode(Funktion[5], INPUT);

	//Beginnen Position
	Servo0.write(1);
	Servo2.write(90);
	Servo1.write(175);
	Servo2.write(120);
	Servo3.write(30);
	Servo4.write(90);
}

void loop() {

	Zunstand	= digitalRead(Selektor); 
	Funktion[0] = digitalRead(Start);
	Funktion[1] = digitalRead(TasterServo0);
	Funktion[2] = digitalRead(TasterServo1);
	Funktion[3] = digitalRead(TasterServo2);
	Funktion[4] = digitalRead(TasterServo3);
	Funktion[5] = digitalRead(TasterServo4);

	// Automatische Funktion
	if (Zunstand == HIGH) {
		// Starte
		if (Funktion[0] != LetzterFunktion[0]) {
			if (Funktion[0] == HIGH) {
				Var[5] = Var[5] + 1;
				delay(250);
			}
		}
		LetzterFunktion[0] = Funktion[0];

		if (Var[5] == 2) { Var[5] = 0; }

		Serial.print("Modus: ");
		if (Zunstand == HIGH) { Serial.println("	-Automatisch-	"); }
		if (Var[5] == 1) { Serial.println("Starte"); }
		if (Var[5] == 1) {
			if (Schritt ==  0) {
				for (int x =   1; x <=  82; x = x + 1) {
					Servo0.write(x);
					delay( 1);
				}
				delay(500);
				Schritt =  1;
			}	
			if (Schritt ==  1) {
				for (int x =  82; x >=   1; x = x - 1) {
					Servo0.write(x);
					delay( 1);
				} delay(500);
				Schritt =  2;
			}	
			if (Schritt ==  2) {
				for (int x = 175; x >= 146; x = x - 1) {
					Servo1.write(x);
					delay(20);
				}
				delay(500);
				Schritt =  3;
			}	
			if (Schritt ==  3) {
				for (int x =  30; x <=  60; x = x + 1) {
					Servo3.write(x);
					delay(20);
				} delay(500);
				Schritt =  4;
			}	
			if (Schritt ==  4) {
				for (int x =  90; x <= 155; x = x + 1) {
					Servo4.write(x);
					delay(20);
				} delay(500);
				Schritt =  5;
			}	
			if (Schritt ==  5) {
				for (int x = 120; x <= 135; x = x + 1) {
					Servo2.write(x);
					delay(20);
				}
				delay(500);
				Schritt =  6;
			}	
			if (Schritt ==  6) {
				for (int x = 180; x >= 100; x = x - 1) {
					Servo4.write(x);
					delay(40);
				}
				delay(500);
				Schritt =  7;
			}	
			if (Schritt ==  7) {
				for (int x = 140; x >= 135; x = x - 1) {
					Servo2.write(x);
					delay(20);
				}
				delay(500);
				Schritt =  8;
			}	
			if (Schritt ==  8) {
				for (int x =  65; x <=  90; x = x + 1) {
					Servo3.write(x);
					delay(20);
				}
				delay(500);
				Schritt =  9;
			}	 
			if (Schritt ==  9) {
				for (int x = 135; x >=  55; x = x - 1) {
					Servo2.write(x);
					delay(20);
				} delay(500);
				Schritt = 10;
			}	
			if (Schritt == 10) {
				for (int x = 146; x >= 108; x = x - 1) {
					Servo1.write(x);
					delay(20);
				}
				delay(500);
				Schritt = 11;
			}	
			if (Schritt == 11) {
				for (int x =  90; x <= 130; x = x + 1) {
					Servo3.write(x);
					delay(20);
				}
				delay(500);
				Schritt = 12;
			}	
			if (Schritt == 12) {
				for (int x =  55; x <= 130; x = x + 1) {
					Servo2.write(x);
					delay(20);
				}
				delay(500);
				Schritt = 13;
			}
			if (Schritt == 13) {
				for (int x = 130; x >= 110; x = x - 1) {
					Servo3.write(x);
					delay(20);
				}
				delay(500);
				Schritt = 14;
			}
			if (Schritt == 14) {
				for (int x = 100; x <= 180; x = x + 1) {
					Servo4.write(x);
					delay(20);
				}
				delay(500);
				Schritt =  0;
			}
			delay(2000);

			Servo0.write(1);
			Servo2.write(90);
			Servo1.write(175);
			Servo2.write(120);
			Servo3.write(30);
			Servo4.write(90);

			delay(500);
			Var[5] = 0;
		}
	}
	// Handarbeit Funktion
	if (Zunstand == LOW) {

		// Servo 0 "Rutsche"
		if (Funktion[1] != LetzterFunktion[1]) {
			if (Funktion[1] == HIGH) {
				Var[0] = Var[0] + 1;
				Var[1] = 0;
				Var[2] = 0;
				Var[3] = 0;
				Var[4] = 0;
				delay(250);
			}
		}
		LetzterFunktion[1] = Funktion[1];
		// Servo1 "Drehgelenk"
		if (Funktion[2] != LetzterFunktion[2]) {
			if (Funktion[2] == HIGH) {
				Var[0] = 0;
				Var[1] = Var[1] + 1;
				Var[2] = 0;
				Var[3] = 0;
				Var[4] = 0;
				delay(250);
			}
		}
		LetzterFunktion[2] = Funktion[2];
		// Servo 2 "Vorzurück"
		if (Funktion[3] != LetzterFunktion[3]) {
			if (Funktion[3] == HIGH) {
				Var[0] = 0;
				Var[1] = 0;
				Var[2] = Var[2] + 1;
				Var[3] = 0;
				Var[4] = 0;
				delay(250);
			}
		}
		LetzterFunktion[3] = Funktion[3];
		// Servo 3 "Abheben"
		if (Funktion[4] != LetzterFunktion[4]) {
			if (Funktion[4] == HIGH) {
				Var[0] = 0;
				Var[1] = 0;
				Var[2] = 0;
				Var[3] = Var[3] + 1;
				Var[4] = 0;
				delay(250);
			}
		}
		LetzterFunktion[4] = Funktion[4];
		// Servo 4 "klammer"
		if (Funktion[5] != LetzterFunktion[5]) {
			if (Funktion[5] == HIGH) {
				Var[0] = 0;
				Var[1] = 0;
				Var[2] = 0;
				Var[3] = 0;
				Var[4] = Var[4] + 1;
				delay(250);
			}
		}
		LetzterFunktion[5] = Funktion[5];

		//Reset die Variablem bei Null
		if (Var[0] == 2) { Var[0] = 0; }
		if (Var[1] == 2) { Var[1] = 0; }
		if (Var[2] == 2) { Var[2] = 0; }
		if (Var[3] == 2) { Var[3] = 0; }
		if (Var[4] == 2) { Var[4] = 0; }

		//Helfen
		/*Funktion map, */
		Grad[0] = map(analogRead(A0), 0, 1023,  0,  82);
		Grad[1] = map(analogRead(A0), 0, 1023, 84, 170);
		Grad[2] = map(analogRead(A0), 0, 1023, 45, 177);
		Grad[3] = map(analogRead(A0), 0, 1023, 46, 140);
		Grad[4] = map(analogRead(A0), 0, 1023, 90, 140);

		if (Var[0] == 1) {Servo0.write(Grad[0]);}
		if (Var[1] == 1) {Servo1.write(Grad[1]);}
		if (Var[2] == 1) {Servo2.write(Grad[2]);}
		if (Var[3] == 1) {Servo3.write(Grad[3]);}
		if (Var[4] == 1) {Servo4.write(Grad[4]);}

		Serial.print("Modus: ");
		if (Zunstand == LOW) { Serial.println("	-Handarbeit-	");
			if (Var[0] == 1) {
				Serial.print(" Servo0: Ein - ");
				Serial.print("Grad bei Servo0: ");
				Serial.println(Grad[0]);
			}
			if (Var[1] == 1) {
				Serial.print(" Servo1: Ein - ");
				Serial.print("Grad bei Servo1: ");
				Serial.println(Grad[1]);
			}
			if (Var[2] == 1) {
				Serial.print(" Servo2: Ein - ");
				Serial.print("Grad bei Servo2: ");
				Serial.println(Grad[2]);
			}
			if (Var[3] == 1) {
				Serial.print(" Servo3: Ein - ");
				Serial.print("Grad bei Servo3: ");
				Serial.println(Grad[3]);
			}
			if (Var[4] == 1) {
				Serial.print(" Servo4: Ein - ");
				Serial.print("Grad bei Servo4: ");
				Serial.println(Grad[4]);
			}
		}
	}
}