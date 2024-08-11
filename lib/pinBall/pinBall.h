#ifndef PINBALL_H
#define PINBALL_H

#include <Arduino.h>

// Define state machine constants
#define PINBALL_IDLE 0
#define PINBALL_LEDS_ON 1
#define PINBALL_COUNT_DOWN 2
#define PINBALL_BLINK 3

// Define timing and other constants
#define DOOR_OPEN 150
#define DOOR_CLOSE 0
#define MOTOR_OFF HIGH
#define MOTOR_ON LOW
#define DOOR_OPEN_TIME_MS 10000
#define EXTRA_TIME_MS 5000

#define DOOR_PIN     2
#define START_SW_PIN 5
#define MOTOR_PIN    13

void initOtherPins();
void FlipperGamestateMachine();

#endif // PINBALL_H
