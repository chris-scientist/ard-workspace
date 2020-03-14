// author: chris-scientist
// created at: 14/03/2020

#ifndef MEGA2560_BUTTON
#define MEGA2560_BUTTON

#include <Arduino.h>

class Button {
  private:
    uint8_t pin;
    uint8_t state;
  public:
    Button(uint8_t aPin);
    void readInput();
    bool pressedBtn();
    bool releasedBtn();
};

#endif
