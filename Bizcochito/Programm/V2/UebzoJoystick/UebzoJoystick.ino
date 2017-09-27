/*
 Name:		UebzoJoystick.ino
 Created:	13/09/2017 10:04:49
 Author:	Julio JSH und Alberto GA
*/

// Bibliothek
//#include <Wire.h>
//#include <Adafruit_MCP23017.h>
#include <Servo.h>


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
Servo Servo0;	// "Rutsche"
Servo Servo1;	// "Drehgelenk"
Servo Servo2;	// "Vorzurück"
Servo Servo3;	// "Abheben"
Servo Servo4;	// "Klammer"

// Variablem
/*Helfen*/
/*
Var[0] Digital real Taster "Starter"
Var[1] Analog read Joystick 1 Poti X
Var[2] Analog read Joystick 1 Poti Y
Var[3] Analog read Joystick 2 Poti X
Var[4] Analog read Joystick 2 Poti Y
Var[5] Digital read Joystick 1 Taster
Var[6] Digital read Joystick 2 Taster
*/
int Var[20];
/*Helfen*/
/*
byte Grad[]{Grad Servo0,Grad Servo1,Grad Servo2,Grad Servo3,Grad Servo4};
*/
byte Grad[]{0,165,80,64,110};

byte Schritt = 0;
boolean Zustand;
/*Helfen*/
/*
Funktion[0] Funktion Starter
Funktion[1] Funktion Joystick 1 Taster 
Funktion[2] Funktion Joystick 2 Taster
*/
boolean Funktion[10];
boolean LetzterFunktion[10];



void setup() {
	//Analog Referez "Default = 5V"
	analogReference(DEFAULT);

	//Serial Beginne
	Serial.begin(9600);

	// Ausgängen bei Servos
	Servo0.attach(3);	// Pin PWM Nummer 3
	Servo1.attach(5);	// Pin PWM Nummer 5 
	Servo2.attach(6);	// Pin PWM Nummer 6
	Servo3.attach(9);	// Pin PWM Nummer 9
	Servo4.attach(10);	// Pin PWM Nummer 10

	//Einstellung bei Arduino Pin
	pinMode(Funktion[0],	INPUT);
	pinMode(Funktion[1],	INPUT);
	pinMode(Selektor,		INPUT);
	pinMode(Starter,		INPUT);
	pinMode(Joystick1,		INPUT);
	pinMode(Joystick2,		INPUT);

	//Beginnen Position
	Servo0.write(Grad[0]);
	Servo1.write(Grad[1]);
	Servo2.write(Grad[2]);
	Servo3.write(Grad[3]);
	Servo4.write(Grad[4]);

}
void Automatisch(byte LetzterPosicion, byte NeuesPosition, String ServoName, byte WebegungZeit){
	/*Helfen*/
	/*
	el primer grupo de if permite aumentar el angulo de cualquiera de los 5 servos con los que cuenta el brayo mientras que el segundo if permite reducir el angulo de los mismos
	la funcion  void Automatisch(LLetzterPosicion, NeuesPosition, ServoName, WebegungZeit, Pause); solo es valida para la funcion de automatico 

	la funcion conpara la posicion incial con la nueva para decidir si tiene que ampliar el angulo o disminuirlo despues cuenta con dos delay con los que controla la velocidad con
	la que realiza la transicion de la pocision inicial a la posicion final y la pausa hasta el siguiente movimiento 
	*/
	if (LetzterPosicion < NeuesPosition){
		if (ServoName == "Servo0") {
			for (int x = LetzterPosicion; x <= NeuesPosition; x = x + 1) { 
				Servo0.write(x); 
				delay(WebegungZeit); 
			} 
			delay(150);
		}
		if (ServoName == "Servo1") { 
			for (int x = LetzterPosicion; x <= NeuesPosition; x = x + 1) {
				Servo1.write(x); 
				delay(WebegungZeit); 
			} 
			delay(150);
		}
		if (ServoName == "Servo2") {
			for (int x = LetzterPosicion; x <= NeuesPosition; x = x + 1) {
				Servo2.write(x);
				delay(WebegungZeit); 
			} 
			delay(150);
		}
		if (ServoName == "Servo3") { 
			for (int x = LetzterPosicion; x <= NeuesPosition; x = x + 1) {
				Servo3.write(x); 
				delay(WebegungZeit); 
			} 
			delay(150);
		}
		if (ServoName == "Servo4") { 
			for (int x = LetzterPosicion; x <= NeuesPosition; x = x + 1) { 
				Servo4.write(x); 
				delay(WebegungZeit); 
			}
			delay(150);
		}
	}
	if (LetzterPosicion > NeuesPosition){
		if (ServoName == "Servo0") { 
			for (int x = LetzterPosicion; x >= NeuesPosition; x = x - 1) {
				Servo0.write(x); 
				delay(WebegungZeit); 
			}
			delay(150);
		}
		if (ServoName == "Servo1") {
			for (int x = LetzterPosicion; x >= NeuesPosition; x = x - 1) { 
				Servo1.write(x);
				delay(WebegungZeit);
			}
			delay(150);
		}
		if (ServoName == "Servo2") {
			for (int x = LetzterPosicion; x >= NeuesPosition; x = x - 1) { 
				Servo2.write(x);
				delay(WebegungZeit);
			}
			delay(150);
		}
		if (ServoName == "Servo3") {
			for (int x = LetzterPosicion; x >= NeuesPosition; x = x - 1) {
				Servo3.write(x);
				delay(WebegungZeit);
			}
			delay(150);
		}
		if (ServoName == "Servo4") {
			for (int x = LetzterPosicion; x >= NeuesPosition; x = x - 1) { 
				Servo4.write(x);
				delay(WebegungZeit); 
			}
			delay(150);
		}
	}
}


void RotacionManual(byte Velocidad) {
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	/*																	 Izquierda																	*/	
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	if (Velocidad == 0) {
		if (Var[1] >= 25 && Var[1] <= 450) {
			Grad[1] = Grad[1] - 1;
		}
	}
	if (Velocidad == 1) {
		if (Var[1] <= 25) {
			Grad[1] = Grad[1] - 10;
		}
	}
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	/*																	 derecha																	*/
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	if (Velocidad == 0) {
		if (Var[1] <= 975 && Var[1] >= 600) {
			Grad[1] = Grad[1] + 1;
		}
	}
	if (Velocidad == 1) {
		if (Var[1] >= 975) {
		Grad[1] = Grad[1] + 10;
		}
	}
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	/*																	 Limite																		*/
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	if (Grad[1] < 11) { Grad[1] = 11; }
	if (Grad[1] > 179) { Grad[1] = 179; }
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	/*																	 Movimiento																	*/
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	Servo1.write(Grad[1]);
}
void ElevacionManual(byte velocidad) {
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	/*																	 Arriba																		*/
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	if (velocidad == 0) {
		if (Var[2] >= 550 && Var[2] <= 975) {
			Grad[2] = Grad[2] + 1;
		}
	}
	if (velocidad == 1) {
		if (Var[2] >= 975) {
			Grad[2] = Grad[2] + 10;
		}
	}
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	/*																	 Abajo																		*/
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	if (velocidad == 0) {
		if (Var[2] <= 450 && Var[2] >= 25) {
			Grad[2] = Grad[2] - 1;
		}
	}
	if (velocidad == 1) {
		if (Var[2] <= 25) {
			Grad[2] = Grad[2] - 10;
		}
	}
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	/*																	 limite																		*/
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	if (Grad[2] < 40) { Grad[2] = 40; }
	if (Grad[2] > 115) { Grad[2] = 115; }
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	/*																	 Movimiento																	*/
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	Servo2.write(Grad[2]);
}
void contracion(byte velocidad) {
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	/*																	 Arriba																		*/
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	if (velocidad == 0) {
		if (Var[4] >= 550 && Var[4] <= 975) {
			Grad[4] = Grad[4] - 1;
		}
	}
	if (velocidad == 1) {
		if (Var[4] >= 975) {
			Grad[4] = Grad[4] - 10;
		}
	}
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	/*																	 Abajo																		*/
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	if (velocidad == 0) {
		if (Var[4] <= 450 && Var[4] >= 25) {
			Grad[4] = Grad[4] + 1;
		}
	}
	if (velocidad == 1) {
		if (Var[4] <= 25) {
			Grad[4] = Grad[4] + 10;
		}
	}
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	/*																	 limite																		*/
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	if (Grad[4] < 35) { Grad[4] = 35; }
	if (Grad[4] > 165) { Grad[4] = 165; }
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	/*																	 Movimiento																	*/
	/*----------------------------------------------------------------------------------------------------------------------------------------------*/
	Servo3.write(Grad[4]);



}


void loop() {
	Zustand = digitalRead(Selektor);
	Funktion[0] = digitalRead(Starter);
	
	// Automatisch Funktion
	if (Zustand == HIGH) {
		// Starte
		if (Funktion[0] != LetzterFunktion[0]) {
			if (Funktion[0] == HIGH) {
				Var[0] = Var[0] + 1;
				delay(250);
			}
		}
		LetzterFunktion[0] = Funktion[0];

		if (Var[0] == 2) { Var[0] = 0; }
		
		

		Serial.print("Modus: ");
		if (Zustand == HIGH) { Serial.println("	-Automatisch-	"); }
		if (Var[0] == 1) { Serial.println("Starte"); }
		if (Var[0] == 1) {
			
			// Automatisch (byte LetzterPosicion, byte NeuesPosition, String ServoName, byte WebegungZeit, int Pause )
			if (Schritt ==  0) { Automatisch(   0,  82, "Servo0",  0); Schritt =  1; }
			if (Schritt ==  1) { Automatisch(  82,   0, "Servo0",  0); Schritt =  2; }
			if (Schritt ==  2) { Automatisch( 165, 118, "Servo1", 25); Schritt =  3; }
			if (Schritt ==  3) { Automatisch(  80,  90, "Servo3", 25); Schritt =  5; }
			if (Schritt ==  5) { Automatisch( 110, 160, "Servo4", 50); Schritt =  6; }
			if (Schritt ==  6) { Automatisch(  90,  80, "Servo3", 25); Schritt =  7; }
			if (Schritt ==  7) { Automatisch(  70,  95, "Servo2", 25); Schritt =  8; }
			if (Schritt ==  8) { Automatisch( 160, 105, "Servo4", 50); Schritt =  9; }
			if (Schritt ==  9) { Automatisch(  90,	85, "Servo2", 25); Schritt = 10; }
			if (Schritt == 10) { Automatisch(  80,  90, "Servo3", 25); Schritt = 11; }
			if (Schritt == 11) { Automatisch(  85,  40, "Servo2", 35); Schritt = 12; }
			if (Schritt == 12) { Automatisch(  90, 140, "Servo3", 45); Schritt = 13; }
			if (Schritt == 13) { Automatisch( 117,  81, "Servo1", 50); Schritt = 14; }
			if (Schritt == 14) { Automatisch( 130, 155, "Servo3", 60); Schritt = 15; }
			if (Schritt == 15) { Automatisch(  40,  90, "Servo2", 75); Schritt = 16; }
			if (Schritt == 16) { Automatisch( 155, 145, "Servo3", 75); Schritt = 17; }
			if (Schritt == 17) { Automatisch( 105, 160, "Servo4", 20); Schritt = 18; }
			if (Schritt == 18) { Automatisch( 160, 110, "Servo4",  5); Schritt = 19; }
			if (Schritt == 19) { Automatisch(  78,  64, "Servo1",  5); Schritt = 20; }
			if (Schritt == 20) { Automatisch(  90,  80, "Servo2",  5); Schritt = 21; }
			if (Schritt == 21) { Automatisch( 145, 165, "Servo3",  5); Schritt =  0; }

			Schritt = 0;
			delay(500);

			// eliminar comentario parar encender bucle
			// borra aqui  <------- Var[0] = 0;
			}
		}

	// Handarbeit Funktion
	if (Zustand == LOW) {

		// Lectura pulsadores joystick 
		Funktion[1] = digitalRead(Joystick1);
		Funktion[2] = digitalRead(Joystick2);

		//Lectura Potenciometros Joystick
		Var[1] = map(analogRead(A0), 0, 1023, 1, 1000);
		Var[2] = map(analogRead(A1), 0, 1023, 1, 1000);
		Var[3] = map(analogRead(A2), 0, 1023, 1, 1000);
		Var[4] = map(analogRead(A3), 0, 1023, 1, 1000);

		// lectura del pulsador del joystick 1
		if (Funktion[1] != LetzterFunktion[1]) {
			if (Funktion[1] == LOW) {
				Var[5] = Var[5] + 1;
			}
		}
		LetzterFunktion[1] = Funktion[1];

		// lectura del pulsador del joystick 2
		if (Funktion[2] != LetzterFunktion[2]) {
			if (Funktion[2] == LOW) {
				Var[6] = Var[6] + 1;
			}
		}
		LetzterFunktion[2] = Funktion[2];

		/*----------------------------------------------------------------------------------------------------------------------------------------------*/
		// Abrir y cerrar la puerta
		if (Var[5] == 1) {
			Servo0.write(82);
			delay(250);
			Servo0.write(1);
			Var[5] = 0;
		}
		/*----------------------------------------------------------------------------------------------------------------------------------------------*/

		RotacionManual(0);
		RotacionManual(1);
		ElevacionManual(0);
		ElevacionManual(1);
		contracion(0);
		contracion(1);

		if (Var[6] == 1) { 
			Servo4.write(160);
			Var[6] = 2;
		}
		if (Var[6] == 3) {
			for (int x = 160; x > 110; x = x - 1) {
				Servo4.write(x);
				delay(50);
			}
			Var[6] = 0;
		}

		







		Serial.print("GRADOS: ");
		Serial.print(Grad[1]);
		Serial.print(" ");
		Serial.print(Grad[2]);
		Serial.print(" ");
		Serial.print(Grad[3]);
		Serial.print(" ");
		Serial.println(Grad[4]);


	}
		}

