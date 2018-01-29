/*
	Keep ISRs short.
	Do not use delay().
	Do not use serial debug.
	Variables shared globally must be volatile.
*/
// #include "LowPower.h"

volatile bool ledOn = false;
const int ledPin = LED_BUILTIN;

void setup() {
	pinMode(ledPin, OUTPUT);
	pinmode(2, INPUT); 
	attachInterrupt(0, buttonPressed, CHANGE);
	//use INT 0 for pin 2 or 
	//use INT 1 for pin 3 for interrupts
	//use LOW, HIGH, RISING, FALLING, or CHANGE
}

void loop() {
	LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
}

void buttonPressed() {
	ledOn = != ledOn;
	digitalWrite(ledPin, ledOn);
	
}