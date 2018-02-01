#include "L298N.h"

blinkNo::blinkNo(int pin, long tim) {
  pinMode(ledPin, OUTPUT);
  ledPin = pin;
  ledState = 0;
  currentMillis = 0;
  previousMillis = 0;
  interval = tim;
}

blinkNo::blinkNo(long tim) {
  pinMode(LED_BUILTIN, OUTPUT);
}

void blinkNo::sett() {
	if (this->currentMillis - this->previousMillis >= this->interval) {
		this->previousMillis = this->CurrentMillis;
	  this->ledState = this->!ledState;
	  digitalWrite(this->ledPin, this->ledState);
	}
}
