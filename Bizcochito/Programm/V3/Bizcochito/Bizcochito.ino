/*
Name:		UebzoJoystick.ino
Created:	13/09/2017 10:04:49
Author:	Julio JSH und Alberto GA
*/

// Bibliothek
	#include <Wire.h>
	#include <Adafruit_MCP23017.h>
	#include <Servo.h>

// MCP23017 16-Bit I/O Expander with Serial Interface
	Adafruit_MCP23017 MCP1;

// Ein-/ Ausgängen bei Arduino
	// Digital
		#define	Selektor	2
		#define Starter		4
		#define Joystick1	7
		#define Joystick2	8

	// Analog
		#define Joystick_1X	A0;
		#define Joystick_1Y	A1;
		#define Joystick_2X A2;
		#define Joystick_2Y	A3;

// Servo
	Servo Servo0;							// "Rutsche"
	Servo Servo1;							// "Drehgelenk"
	Servo Servo2;							// "Vorzurück"
	Servo Servo3;							// "Abheben"
	Servo Servo4;							// "Klammer"

// Variablem
	boolean Geschwindigkeit;				//

//Schalter
	boolean Zustand1;						//


// Taster
	boolean TasterS0;						// Digital read Taster "Starter"
	boolean Zustand2;						// Digital read Taster "Joystick oder Taster" MCP1
	boolean TasterJY1;						// Digital read Joystick 1 Taster
	boolean TasterJY2;						// Digital read Joystick 2 Taster

// Poti
	byte PotiJY_X1;							// Analog read Joystick 1 Poti X
	byte PotiJY_Y1;							// Analog read Joystick 1 Poti Y
	byte PotiJY_X2;							// Analog read Joystick 2 Poti X
	byte PotiJY_Y2;							// Analog read Joystick 2 Poti Y

// Grade bei Servos
	byte Grad0 =   0;
	byte Grad1 = 165;
	byte Grad2 =  80;
	byte Grad3 =  64;
	byte Grad4 = 110;

// Schritte bei Automatische Funktion
	byte Schritt = 0;

// Funktion Starter
	boolean FunktionStarter;
	boolean LetzterFunktionStarter;

// Funktion  Taster Joystick 1
	boolean FunktionTaster_Joystick1;
	boolean LetzterFunktionTaster_Joystick1;

// Funktion  Taster Joystick 2
	boolean FunktionTaster_Joystick2;
	boolean LetzterFunktionTaster_Joystick2;

void setup() {
// Starte die MCP23017 mit addresse 0x20
	MCP1.begin(0);

// Analog Referez "Default = 5V"
	analogReference(DEFAULT);

// Serial Beginne
	Serial.begin(9600);

// Ausgängen bei Servos
	Servo0.attach( 3);						// Pin PWM Nummer 3
	Servo1.attach( 5);						// Pin PWM Nummer 5 
	Servo2.attach( 6);						// Pin PWM Nummer 6
	Servo3.attach( 9);						// Pin PWM Nummer 9
	Servo4.attach(10);						// Pin PWM Nummer 10

// Einstellung bei Arduino Pin
	pinMode(Selektor,	INPUT);
	pinMode(Starter,	INPUT);
	pinMode(Joystick1,	INPUT);
	pinMode(Joystick2,	INPUT);

// Einstellung bei MCP23017 Pin
	MCP1.pinMode(0,		INPUT);				// Selektor Joystick oder Taster
	MCP1.pinMode(1,		INPUT); 			// Geschwindigkeit
	MCP1.pinMode(2,		INPUT);				// Servo0 +
	MCP1.pinMode(3,		INPUT); 			// Servo0 -
	MCP1.pinMode(4,		INPUT);				// Servo1 +
	MCP1.pinMode(5,		INPUT); 			// Servo1 -
	MCP1.pinMode(6,		INPUT);				// Servo2 +
	MCP1.pinMode(7,		INPUT);				// Servo2 -
	MCP1.pinMode(8,		INPUT);				// Servo3 +
	MCP1.pinMode(9,		INPUT);				// Servo3 -
	MCP1.pinMode(10,	INPUT);				// Servo4 +
	MCP1.pinMode(10,	INPUT);				// Servo4 -


//Beginnen Position
	Servo0.write(Grad0);
	Servo1.write(Grad1);
	Servo2.write(Grad2);
	Servo3.write(Grad3);
	Servo4.write(Grad4);

}

void Automatisch(byte LetzterPosicion, byte NeuesPosition, String ServoName, byte WebegungZeit) {

	long previousMillis = 0;
	unsigned long currentMillis = millis();
	byte interval = 0;

	if (LetzterPosicion < NeuesPosition) {
		if (ServoName == "Servo0") {
			for (int x = LetzterPosicion; x <= NeuesPosition; x = x + 1) {
				Servo0.write(x);
				if (currentMillis - previousMillis > WebegungZeit) {
					previousMillis = currentMillis;
					if (interval == 0) {
						interval = 1;
					}
					else
						interval = 0;
				}
			}
			if (currentMillis - previousMillis > 150) {
				previousMillis = currentMillis;
				if (interval == 0) {
					interval = 1;
				}
				else
					interval = 0;
			}
		}
		if (ServoName == "Servo1") {
			for (int x = LetzterPosicion; x <= NeuesPosition; x = x + 1) {
				Servo1.write(x);
				if (currentMillis - previousMillis > WebegungZeit) {
					previousMillis = currentMillis;
					if (interval == 0) {
						interval = 1;
					}
					else
						interval = 0;
				}
			}
			if (currentMillis - previousMillis > 150) {
				previousMillis = currentMillis;
				if (interval == 0) {
					interval = 1;
				}
				else
					interval = 0;
			}
		}
		if (ServoName == "Servo2") {
			for (int x = LetzterPosicion; x <= NeuesPosition; x = x + 1) {
				Servo2.write(x);
				if (currentMillis - previousMillis > WebegungZeit) {
					previousMillis = currentMillis;
					if (interval == 0) {
						interval = 1;
					}
					else
						interval = 0;
				}
			}
			if (currentMillis - previousMillis > 150) {
				previousMillis = currentMillis;
				if (interval == 0) {
					interval = 1;
				}
				else
					interval = 0;
			}
		}
		if (ServoName == "Servo3") {
			for (int x = LetzterPosicion; x <= NeuesPosition; x = x + 1) {
				Servo3.write(x);
				if (currentMillis - previousMillis > WebegungZeit) {
					previousMillis = currentMillis;
					if (interval == 0) {
						interval = 1;
					}
					else
						interval = 0;
				}
			}
			if (currentMillis - previousMillis > 150) {
				previousMillis = currentMillis;
				if (interval == 0) {
					interval = 1;
				}
				else
					interval = 0;
			}
		}
		if (ServoName == "Servo4") {
			for (int x = LetzterPosicion; x <= NeuesPosition; x = x + 1) {
				Servo4.write(x);
				if (currentMillis - previousMillis > WebegungZeit) {
					previousMillis = currentMillis;
					if (interval == 0) {
						interval = 1;
					}
					else
						interval = 0;
				}
			}
			if (currentMillis - previousMillis > 150) {
				previousMillis = currentMillis;
				if (interval == 0) {
					interval = 1;
				}
				else
					interval = 0;
			}
		}
	}
	if (LetzterPosicion > NeuesPosition) {
		if (ServoName == "Servo0") {
			for (int x = LetzterPosicion; x >= NeuesPosition; x = x - 1) {
				Servo0.write(x);
				if (currentMillis - previousMillis > WebegungZeit) {
					previousMillis = currentMillis;
					if (interval == 0) {
						interval = 1;
					}
					else
						interval = 0;
				}
				if (currentMillis - previousMillis > 150) {
					previousMillis = currentMillis;
					if (interval == 0) {
						interval = 1;
					}
					else
						interval = 0;
				}

			}
		}
		if (ServoName == "Servo1") {
			for (int x = LetzterPosicion; x >= NeuesPosition; x = x - 1) {
				Servo1.write(x);
				if (currentMillis - previousMillis > WebegungZeit) {
					previousMillis = currentMillis;
					if (interval == 0) {
						interval = 1;
					}
					else
						interval = 0;
				}
				if (currentMillis - previousMillis > 150) {
					previousMillis = currentMillis;
					if (interval == 0) {
						interval = 1;
					}
					else
						interval = 0;
				}

			}
		}
		if (ServoName == "Servo2") {
			for (int x = LetzterPosicion; x >= NeuesPosition; x = x - 1) {
				Servo2.write(x);
				if (currentMillis - previousMillis > WebegungZeit) {
					previousMillis = currentMillis;
					if (interval == 0) {
						interval = 1;
					}
					else
						interval = 0;
				}
				if (currentMillis - previousMillis > 150) {
					previousMillis = currentMillis;
					if (interval == 0) {
						interval = 1;
					}
					else
						interval = 0;
				}

			}
		}
		if (ServoName == "Servo3") {
			for (int x = LetzterPosicion; x >= NeuesPosition; x = x - 1) {
				Servo3.write(x);
				if (currentMillis - previousMillis > WebegungZeit) {
					previousMillis = currentMillis;
					if (interval == 0) {
						interval = 1;
					}
					else
						interval = 0;
				}
				if (currentMillis - previousMillis > 150) {
					previousMillis = currentMillis;
					if (interval == 0) {
						interval = 1;
					}
					else
						interval = 0;
				}

			}
		}
		if (ServoName == "Servo4") {
			for (int x = LetzterPosicion; x >= NeuesPosition; x = x - 1) {
				Servo4.write(x);
				if (currentMillis - previousMillis > WebegungZeit) {
					previousMillis = currentMillis;
					if (interval == 0) {
						interval = 1;
					}
					else
						interval = 0;
				}
				if (currentMillis - previousMillis > 150) {
					previousMillis = currentMillis;
					if (interval == 0) {
						interval = 1;
					}
					else
						interval = 0;
				}

			}
		}
	}
}

void ManualeDrehung() {
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/*																	 Links																		*/
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	if (PotiJY_X1 >= -86 && PotiJY_X1 <= -20) {
		Grad1 = Grad1 - 1;
	}
	if (PotiJY_X1 <= -85) {
		Grad1 = Grad1 - 10;
	}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/*																	 Rechts																		*/
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	if (PotiJY_X1 <= 84 && PotiJY_X1 >= 20) {
		Grad1 = Grad1 + 1;
	}
	if (PotiJY_X1 >= 85) {
		Grad1 = Grad1 + 10;
	}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/*																	 Limite																		*/
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	if (Grad1 <  11) { Grad1 =  11; }
	if (Grad1 > 179) { Grad1 = 179; }
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/*																	 Bewegung																	*/
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	Servo1.write(Grad1);
}




