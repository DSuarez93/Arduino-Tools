/*
	Use this instead of the sketchbook Blink.
	It is a timer which does not require polling by stalling the program.
	millis() accounts for the amount of time after the board advances into the loop function.
	Comparing this time to a set interval will create a timer.
*/

const int ledPin = LED_BUILTIN;
volatile bool ledState = 0;
unsigned long previousMillis = 0;
unsigned long currentMillis;
const long interval = 250;

void setup() {
	pinMode(ledPin, OUTPUT);
	currentMillis = 0;
}

void sett() {
	if (currentMillis - previousMillis >= interval) {
		previousMillis = currentMillis;
		action();
	}
}

void action() {
	ledState = !ledState;
	digitalWrite(ledPin, ledState);
	//insert other code
}

void loop() {
	currentMillis = millis();
	sett();
}
