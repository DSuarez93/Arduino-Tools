/*
	http://www.youtube.com/watch?v=kv-9mxVaVzE	
	PWM sets speed of a motor.
	Next two pins control direction.
	PWM needs to be high enough to spin the motor, but introduce a capacitor in order to clean up square pulses.
*/

const int reef = 180;
int sPWM;			//control the speed of the motor
const int pinPWM = 11;		
const int direction1 = 12;
const int direction2 = 13;
volatile boolean switcher;		//dictates a direction
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
const long interval = 1500;

void sett() {
	currentMillis = millis();
	if (currentMillis - previousMillis >= interval) {
		previousMillis = currentMillis;
		rotate();
	}
}

void rotate() {
	if (switcher) {
	  sPWM = reef - 40; forward();
	} else {
	  sPWM = reef + 40; backward();
	}
	switcher = !switcher;
	analogWrite(pinPWM, sPWM);
}

void forward() {
  digitalWrite(direction1, HIGH);
  digitalWrite(direction2, LOW);
}

void backward() {
  digitalWrite(direction1, LOW);
  digitalWrite(direction2, HIGH);
}

void setup() {
  pinMode(direction1, OUTPUT);
	pinMode(direction2, OUTPUT);
	pinMode(pinPWM, OUTPUT);
	switcher = false;
}

void loop() {
  sPWM = reef;
  sett();
}
