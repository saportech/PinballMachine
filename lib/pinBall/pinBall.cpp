#include "pinBall.h"

void initOtherPins() {
    pinMode(DOOR_PIN, OUTPUT);
    pinMode(START_SW_PIN, INPUT_PULLUP);
    pinMode(MOTOR_PIN, OUTPUT);

    // Set all pins to LOW
    digitalWrite(DOOR_PIN, HIGH);
    digitalWrite(MOTOR_PIN, HIGH);
}
