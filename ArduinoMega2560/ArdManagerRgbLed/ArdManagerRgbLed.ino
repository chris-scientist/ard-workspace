// author: chris-scientist
// created by: 14/03/2020
//
// /-------------------------------------------------------------------------------\
// | Description:                                                                  |
// |                                                                               |
// | * This program is design for Arduino MEGA 2560.                               |
// |                                                                               |
// | * It's manager of RGB LED, driven by 3 buttons,                               |
// |   and 3 monochromes LED indicator.                                            |
// |   An only RGB LED to show the color.                                          |
// |   One button to change the driven component,                                  |
// |   an other button to increment the value of current component                 |
// |   and the last button to decrement the value of current component.            |
// |   Red LED turned on if the driven component is red (default component).       |
// |   Green LED turned on if the driven component is green.                       |
// |   Blue LED turned on if the driven component is blue.                         |
// |                                                                               |
// | * The RGB LED use the pins 2, 3 and 4.                                        |
// |   To change :                                                                 |
// |   * The red component PIN : replace the PIN_RED_COMPONENT value by your PIN.  |
// |   * The green component PIN : replace the PIN_GREEN_COMPONENT value           |
// |     by your PIN.                                                              |
// |   * The blue component PIN : replace the PIN_BLUE_COMPONENT value             |
// |     by your PIN.                                                              |
// |                                                                               |
// | * The buttons use the pins 30, 31 and 32.                                     |
// |   To change :                                                                 |
// |   * The driven component button : replace the PIN_COMPONENT_BTN value         |
// |     by your PIN.                                                              |
// |   * The increment button : replace the PIN_INCREMENT_BTN value by your PIN.   |
// |   * The decrement button : replace the PIN_DECREMENR_BTN value by your PIN.   |
// |                                                                               |
// | * The LEDs, used to manage component indicator, use the pins 40, 41 and 42.   |
// |   To change :                                                                 |
// |   * The start PIN of LED : replace the PIN_START_LED value by your PIN.       |
// |   * The number of LED : replace the LED_COUNT value by your number of LED.    |
// |                                                                               |
// | * The program is updated at 25 Hz.                                            |
// |                                                                               |
// | * To see the result, send me a email at :                                     |
// |   chris <dot> scientist <dot> contact <at> gmail <dot> com                    |
// |   With the following object mail :                                            |
// |   SAMPLE_MANAGER_RGB_LED_3_BTN                                                |
// |                                                                               |
// \-------------------------------------------------------------------------------/

#include "Button.h"
#include "LedRgb.h"

#define PIN_START_LED 40
#define LED_COUNT 3
#define PIN_COMPONENT_BTN 30
#define PIN_INCREMENT_BTN 31
#define PIN_DECREMENT_BTN 32
#define PIN_RED_COMPONENT 2
#define PIN_GREEN_COMPONENT 3
#define PIN_BLUE_COMPONENT 4

// Pulsation frequence
// here equal to 25 Hz
const uint8_t PULSE_DURATION = 40; // period of pulsation (in milliseconds)

struct Timer {
  uint32_t last;
  uint32_t beats;
};

Timer timer = { 0, 0 };

Button * componentBtn = NULL;
Button * incrementBtn = NULL;
Button * decrementBtn = NULL;
LedRgb * ledRgb = NULL;

void setup() {
  // Initialize Timer
  timer.last  = millis();
  timer.beats = 0;
  // Initialize LEDs
  for(uint8_t itLed = 0 ; itLed < LED_COUNT ; itLed++) {
    pinMode(PIN_START_LED+itLed, OUTPUT);
  }
  // Initialize RGB LED
  ledRgb = new LedRgb(PIN_RED_COMPONENT, PIN_GREEN_COMPONENT, PIN_BLUE_COMPONENT, true);
  ledRgb->updateColor();
  // Initialize buttons
  componentBtn = new Button(PIN_COMPONENT_BTN);
  incrementBtn = new Button(PIN_INCREMENT_BTN);
  decrementBtn = new Button(PIN_DECREMENT_BTN);
}

void loop() {
  waitForUpdate();
  // Manage buttons
  if(componentBtn->releasedBtn()) {
    ledRgb->nextComponent();
  } else if(incrementBtn->repeatedBtn()) {
    ledRgb->incrementCurrentComponent();
  } else if(decrementBtn->repeatedBtn()) {
    ledRgb->decrementCurrentComponent();
  }
  // Manage (animation of) LEDs
  manageIndicator();
  ledRgb->updateColor();
}

// Make animation on monochrome LED
void manageIndicator() {
  // Manage LED indicator of selected component
  for(uint8_t itLed = 0 ; itLed < LED_COUNT ; itLed++) {
    digitalWrite(PIN_START_LED+itLed, (ledRgb->getCurrentIndexComponent() == itLed) ? HIGH : LOW);
  }
}

void updateAllInput() {
  componentBtn->readInput();
  incrementBtn->readInput();
  decrementBtn->readInput();
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
