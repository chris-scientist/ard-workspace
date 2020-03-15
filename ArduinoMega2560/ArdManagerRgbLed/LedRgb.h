// author: chris-scientist
// created at: 14/03/2020

#ifndef MEGA2560_LED_RGB
#define MEGA2560_LED_RGB

#include <Arduino.h>

class LedRgb {
  private:
    uint8_t redComponent;
    uint8_t greenComponent;
    uint8_t blueComponent;
    uint8_t currentIndexComponent; // 0 = Red, 1 = Green and 2 = Blue
    uint8_t pin4Red;
    uint8_t pin4Green;
    uint8_t pin4Blue;
    const bool isCommonAnode;

    uint8_t computeComponent(uint8_t aComponet);
  public:
    LedRgb(uint8_t aPin4Red, uint8_t aPin4Green, uint8_t aPin4Blue, const bool isCommonAnode);
    void incrementCurrentComponent();
    void decrementCurrentComponent();
    void updateColor();
    void nextComponent();
    uint8_t getCurrentIndexComponent();
};

#endif
