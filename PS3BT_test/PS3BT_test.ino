#include <PS3BT.h>
#include <usbhub.h>
#include <SPI.h>

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57);
bool switching;

void setup() {
  Serial.begin(115200);
  switching = 0;
  #if !defined(__MIPSEL__)
    while (!Serial);
  #endif
  if (Usb.Init() ==-1) {
    while(1) {
      digitalWrite(LED_BUILTIN, switching);
      switching = !switching;
      delay(500);
    }
  }
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  for (int i = 0; i<6; i++) {
    digitalWrite(LED_BUILTIN, switching);
    switching = !switching;
    delay(200);
  }
}

void loop() {
  Usb.Task();
  if (PS3.PS3Connected) {
    if (PS3.getButtonClick(PS) && PS3.getButtonClick(L2) && PS3.getButtonClick(R1)) {
      PS3.disconnect();
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
          digitalWrite(5, switcher); switcher != switcher;
    }
    if (PS3.getButtonClick(TRIANGLE)) {
          digitalWrite(4, switcher); switcher != switcher;
    }
    if (PS3.getButtonClick(CROSS)) {
          PS3.setRubmledOn(RumbleLow);
    }
    if (PS3.getButtonClick(CIRCLE)) {
          PS3.setRumbleOn(RumbleHigh);
    }
  }    //end PS3 Connect
}
