#include <PS3BT.h>
#include <usbhub.h>
#include <SPI.h>

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57);
bool switching, sw1, sw2, sw3;
const byte ledPin =   3;
const byte testPin =  4;       //stop
const byte move =     5;       //forward
const byte ootw =     6;       //reverse

void setup() {
  Serial.begin(115200);
  switching = 1; sw1 = 1; sw2 = 1; sw3 = 1;
  #if !defined(__MIPSEL__)
    while (!Serial);
  #endif
  if (Usb.Init() ==-1) {
    while(1) {
      digitalWrite(ledPin, switching);
      switching = !switching;
      delay(500);
    }
  }
  pinMode(ledPin, OUTPUT);
  for (int i = 0; i<6; i++) {
    digitalWrite(ledPin, switching);
    switching = !switching;
    delay(200);
  }
}

void setHigh() {
//digitalWrite(ledPin, HIGH);
  digitalWrite(testPin, HIGH);
  digitalWrite(move, HIGH);
  digitalWrite(ootw, HIGH);
  switching = 1; sw1=1; sw2=1; sw3 = 1;  
}

void loop() {
  Usb.Task();
  setHigh();
  if (PS3.PS3Connected) {
    if (PS3.getButtonPress(PS) && PS3.getButtonPress(L2) && PS3.getButtonPress(R1)) {
      PS3.disconnect(); digitalWrite(testPin, LOW);
    }
    if (PS3.getButtonClick(UP)) {
          PS3.setLedOff();
          PS3.setLedOn(LED4);
    }
    if (PS3.getButtonClick(RIGHT)) {
          PS3.setLedOff();
          PS3.setLedOn(LED1);
    }
    if (PS3.getButtonClick(DOWN)) {
          PS3.setLedOff();
          PS3.setLedOn(LED2);
    }
    if (PS3.getButtonClick(LEFT)) {
          PS3.setLedOff();
          PS3.setLedOn(LED3);
    }
    if (PS3.getButtonClick(SQUARE)) {
        switching = !switching;
    }
    if (PS3.getButtonClick(TRIANGLE)) {
        sw1 = !sw1;
    }
    if (PS3.getButtonClick(CROSS)) {
        PS3.setRumbleOn(RumbleLow);
    }
    if (PS3.getButtonClick(CIRCLE)) {
        PS3.setRumbleOn(RumbleHigh);
    }
    if (PS3.getButtonClick(R1)) {
        sw2 = !sw2;
    }
    if (PS3.getButtonClick(L1)) {
    }
    if (PS3.getButtonClick(L3)) {
    }
    if (PS3.getButtonClick(R3)) {
    }
    if (PS3.getButtonClick(L2)) {
    }    
    if (PS3.getButtonClick(R2)) {
    }    
  }  else digitalWrite(testPin, LOW);  //end PS3 Connect
  digitalWrite(ledPin, switching);
  digitalWrite(move, sw1);
  digitalWrite(ootw, sw2);
}
