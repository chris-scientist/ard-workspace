// author: chris-scientist
// created at: 14/03/2020

#include "LedRgb.h"

LedRgb::LedRgb(uint8_t aPin4Red, uint8_t aPin4Green, uint8_t aPin4Blue, const bool isCommonAnode)
 :
  pin4Red(aPin4Red), 
  pin4Green(aPin4Green),
  pin4Blue(aPin4Blue),
  redComponent(0),
  greenComponent(0),
  blueComponent(0),
  currentIndexComponent(0),
  isCommonAnode(isCommonAnode)
{
  pinMode(pin4Red, OUTPUT);
  pinMode(pin4Green, OUTPUT);
  pinMode(pin4Blue, OUTPUT);
}

void LedRgb::incrementCurrentComponent() {
  switch(currentIndexComponent) {
    case 0: // Red
      if(redComponent < 255) {
        redComponent++;
      }
    break;
    case 1: // Green
      if(greenComponent < 255) {
        greenComponent++;
      }
    break;
    case 2: // Blue
      if(blueComponent < 255) {
        blueComponent++;
      }
    break;
  }
}

void LedRgb::decrementCurrentComponent() {
  switch(currentIndexComponent) {
    case 0: // Red
      if(redComponent > 0) {
        redComponent--;
      }
    break;
    case 1: // Green
      if(greenComponent > 0) {
        greenComponent--;
      }
    break;
    case 2: // Blue
      if(blueComponent > 0) {
        blueComponent--;
      }
    break;
  }
}

void LedRgb::updateColor() {
  analogWrite(pin4Red, computeComponent(redComponent));
  analogWrite(pin4Green, computeComponent(greenComponent));
  analogWrite(pin4Blue, computeComponent(blueComponent));
}

void LedRgb::nextComponent() {
  ++currentIndexComponent %= 3;
}

uint8_t LedRgb::getCurrentIndexComponent() {
  return currentIndexComponent;
}

uint8_t LedRgb::computeComponent(uint8_t aComponent) {
  return (isCommonAnode ? (255 - aComponent) : aComponent);
}
