#ifndef blinkNoDelay.h
#define blinkNoDelay.h

#include "Arduino.h"

class blinkNo
{
  public:
    blinkNo(int pin, long tim);
    void sett();
  private:
    int ledPin;
    bool ledState;
    long previousMillis;
    long currentMillis;
    long interval;
};

#endif
