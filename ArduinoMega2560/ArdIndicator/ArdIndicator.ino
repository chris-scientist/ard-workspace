// author: chris-scientist
// created by: 14/03/2020
//
// /-------------------------------------------------------------------------------\
// | Description:                                                                  |
// |                                                                               |
// | * This program is design for Arduino MEGA 2560.                               |
// |                                                                               |
// | * It's manager of mono-indicator, the 5 LED, driven by 2 buttons.             |
// |   One button to indicate to go to left and other to indicate to go to right.  |
// |                                                                               |
// | * The LED use the pins 40, 41, 42, 43, 44.                                    |
// |   To change :                                                                 |
// |   * The start PIN of LED : replace the PIN_START_LED value by your PIN.       |
// |   * The number of LED : replace the LED_COUNT value by your number of LED.    |
// |                                                                               |
// | * The left button use the pin 30, and the right button use pin 31.            |
// |   To change :                                                                 |
// |   * The left button PIN : replace the PIN_LEFT_BTN value by your PIN.         |
// |   * The right button PIN : replace the PIN_RIGHT_BTN value by your PIN.       |
// |                                                                               |
// | * The program is updated at 25 Hz.                                            |
// |                                                                               |
// | * To see the result, send me a email at :                                     |
// |   chris <dot> scientist <dot> contact <at> gmail <dot> com                    |
// |   With the following object mail :                                            |
// |   SAMPLE_INDICATOR_5_LED_2_BTN                                                |
// |                                                                               |
// \-------------------------------------------------------------------------------/

#include "Button.h"

#define PIN_START_LED 40
#define LED_COUNT 5
#define PIN_LEFT_BTN 30
#define PIN_RIGHT_BTN 31

// Pulsation frequence
// here equal to 25 Hz
const uint8_t PULSE_DURATION = 40; // period of pulsation (in milliseconds)

struct Timer {
  uint32_t last;
  uint32_t beats;
};

Timer timer = { 0, 0 };

Button * leftBtn = NULL;
Button * rightBtn = NULL;

bool increment = true;
uint8_t offset;
const uint8_t MAX_PERIOD = 5;
uint8_t periodOfAnimation = 0;
bool runAnimation = false;

void setup() {
  // Initialize Timer
  timer.last  = millis();
  timer.beats = 0;
  // Initialize LEDs
  for(uint8_t itLed = 0 ; itLed < LED_COUNT ; itLed++) {
    pinMode(PIN_START_LED+itLed, OUTPUT);
  }
  // Initialize buttons
  leftBtn = new Button(PIN_LEFT_BTN);
  rightBtn = new Button(PIN_RIGHT_BTN);
  // Initialize counter
  offset = (increment ? 0 : 4);
}

void loop() {
  waitForUpdate();
  // Manage buttons
  if(leftBtn->releasedBtn()) {
    updateIndicator(false);
  } else if(rightBtn->releasedBtn()) {
    updateIndicator(true);
  }
  // Manage (animation of) LEDs
  if(runAnimation && periodOfAnimation < MAX_PERIOD) {
    manageIndicator();
  } else {
    runAnimation = false;
    periodOfAnimation = 0;
    resetIndicator();
  }
}

// Make animation on LED
void manageIndicator() {
  if(timer.beats % 4 == 0) {
    // update LEDs
    for(uint8_t itLed = 0 ; itLed < LED_COUNT ; itLed++) {
      digitalWrite(PIN_START_LED+itLed, (offset == itLed) ? HIGH : LOW);
    }

    if(increment) {
      if(offset < 4) {
        offset++;
      } else {
        offset = 0;
        periodOfAnimation++;
      }
    } else {
      if(offset > 0) {
        offset--;
      } else {
        offset = 4;
        periodOfAnimation++;
      }
    }
  }
}

// Turn off all LED
void resetIndicator() {
  for(uint8_t itLed = 0 ; itLed < LED_COUNT ; itLed++) {
    digitalWrite(PIN_START_LED+itLed, LOW);
  }
}

void updateIndicator(bool isIncrement) {
  increment = isIncrement;
  offset = (increment ? 0 : 4);
  runAnimation = true;
  resetIndicator();
}

void updateAllInput() {
  leftBtn->readInput();
  rightBtn->readInput();
}

void waitForUpdate() {
  uint32_t now;
  updateAllInput();
  do {
    now = millis();
  } while (now - timer.last < PULSE_DURATION);
  timer.last = now;
  timer.beats++;
}
