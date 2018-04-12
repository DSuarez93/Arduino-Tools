/*
  Program this sketch to Mega 2560 and connect to Arduino Uno with Bluetooth Host Shield.
  Establish a common ground when using the two microcotrollers.
  Connect a resistor to the Analog In Wire
  AnalogRead values range from 0 to 1023
  Use with PS3BT_Test
*/

volatile int motorSpeed = 128; //according to PWM, 2^8-1 is max speed in one direction

//Pins
const int ledPin = LED_BUILTIN;
const int one_one = 2;
const int one_two = 3;
const int one_pwm = 4;
const int two_one = 5;
const int two_two = 6;
const int two_pwm = 7;
const int three_one = 8;
const int three_two = 9;
const int three_pwm = 10;
const int four_one = 11;
const int four_two = 12;
const int four_pwm = 13;
const int readIn = 14;
const int tens = 15;
const int hundreds = 16;

unsigned long previousMillis = 0;
unsigned long currentMillis;
const long interval = 1000;
bool toggle;
volatile bool ledOn;
int readValue;

void Pins() {
  pinMode(one_one, OUTPUT);
	pinMode(one_two, OUTPUT);
	pinMode(one_pwm, OUTPUT);
  pinMode(two_one, OUTPUT);
	pinMode(two_two, OUTPUT);
	pinMode(two_pwm, OUTPUT);	
  pinMode(three_one, OUTPUT);
	pinMode(three_two, OUTPUT);
	pinMode(three_pwm, OUTPUT);
  pinMode(four_one, OUTPUT);
	pinMode(four_two, OUTPUT);
	pinMode(four_pwm, OUTPUT);	
	pinMode(readIn, INPUT_PULLUP);
	pinMode(tens, INPUT_PULLUP);
	pinMode(hundreds, INPUT_PULLUP);
}

void getIn() {
  bool ones, twos, threes;
  ones = digitalRead(readIn);
  twos = digitalRead(tens);
  threes = digitalRead(hundreds);
  if(!threes && !twos && ones) {  //case 3
    carTurn(true); return;
  }
  if(!threes && twos && !ones) {  //case 2
    carTurn(false); return;
  }
  if(!threes && twos && ones) {   //case 1
    forward(true); return;
  }
  if(threes && !twos && !ones) {  //case 4
    forward(false); return;
  }
  stopMotor();
}

void setup() {
	Pins();
  stopMotor();
	currentMillis = 0;
	ledOn = false;
	toggle = LOW;
}

void sett() {
	if (currentMillis - previousMillis >= interval) {
		previousMillis = currentMillis;
		action();
	}
}

void action() {
  digitalWrite(ledPin, ledOn); ledOn = !ledOn;
}


void carTurn(bool dir) {
  //when called, read another digital pin to dictate lef or rig
  if (dir) toggle = HIGH; else toggle = LOW;
  digitalWrite(one_one, toggle); 
  digitalWrite(one_two, toggle); toggle = !toggle;
  digitalWrite(two_one, toggle); 
  digitalWrite(two_two, toggle); toggle =!toggle;
  digitalWrite(three_one, toggle); 
  digitalWrite(three_two, toggle); toggle =!toggle;
  digitalWrite(four_one, toggle); 
  digitalWrite(four_two, toggle); toggle =!toggle;  
  analogWrite(one_pwm, motorSpeed);
  analogWrite(two_pwm, motorSpeed);
  analogWrite(three_pwm, motorSpeed);
  analogWrite(four_pwm, motorSpeed);
}


void stopMotor() {
  digitalWrite(one_one, LOW);
  digitalWrite(one_two, LOW);
  analogWrite(one_pwm, 0);
  digitalWrite(two_one, LOW);
  digitalWrite(two_two, LOW);
  analogWrite(two_pwm, 0);
  digitalWrite(three_one, LOW);
  digitalWrite(three_two, LOW);
  analogWrite(three_pwm, 0);
  digitalWrite(four_one, LOW);
  digitalWrite(four_two, LOW);
  analogWrite(four_pwm, 0);
  
}
void forward(bool really) {
  if (really) toggle = HIGH; else toggle = LOW;
  digitalWrite(one_one, toggle); toggle = !toggle;
  digitalWrite(one_two, toggle); toggle = !toggle;
  digitalWrite(two_one, toggle); toggle = !toggle;
  digitalWrite(two_two, toggle); toggle = !toggle;
  digitalWrite(three_one, toggle); toggle = !toggle;
  digitalWrite(three_two, toggle); toggle = !toggle;  
  digitalWrite(four_one, toggle); toggle = !toggle;
  digitalWrite(four_two, toggle); toggle = !toggle;  
  analogWrite(one_pwm, motorSpeed);
  analogWrite(two_pwm, motorSpeed);
  analogWrite(three_pwm, motorSpeed);
  analogWrite(four_pwm, motorSpeed);
}

void loop() {
	currentMillis = millis();
	sett();       //disable if using real-time
	getIn();
	//action();   //disable if using a timer
}
