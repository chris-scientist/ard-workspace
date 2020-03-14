// author: chris-scientist
// created at: 14/03/2020

#include "Button.h"

Button::Button(uint8_t aPin) : pin(aPin), state(0) {
  pinMode(this->pin, INPUT);
}

void Button::readInput() {
  bool isPressedBtn = (digitalRead(this->pin) == LOW);
  if(isPressedBtn) {
    if(this->state < 0xFE) {
      this->state++;
    } else if(this->state == 0xFE) {
      this->state = 2;
    }
  } else if(this->state) {
    this->state = (this->state == 0xFF) ? 0 : 0xFF;
  }
}

bool Button::pressedBtn() {
  return (this->state == 1);
}

bool Button::releasedBtn() {
  return (this->state == 0xFF);
}
