#include <Arduino.h>
#include "pinBall.h"
#include "Leds.h"
#include "Flippers.h"

int pinball_state = PINBALL_IDLE;

Leds ledsObj;
Flippers flippers;

int button[7] = {33, 32, 35, 39, 12, 36, 5};

void testInputs() {
    for (int i = 0; i < 7; i++) {
        int val = digitalRead(button[i]);
        if (val == LOW) {
          // if (i=!1) {
            Serial.print("Button ");
            Serial.print(i + 1);  // Adjust for 1-based indexing in the output
            Serial.println(" pressed");
            delay(200);
          //}

        }
    }
}


void setup() {
    Serial.begin(115200);
    Serial.println("Flippers");
    initOtherPins();
    ledsObj.init();
    flippers.init();
}

void loop() {

    //testInputs();

    FlipperGamestateMachine();

}

void FlipperGamestateMachine() {

static unsigned long lastMillis;

    switch (pinball_state) {
        case PINBALL_IDLE:
            if (digitalRead(START_SW_PIN) == LOW) {
                Serial.println("Starting, Door opened, leds ON");
                digitalWrite(DOOR_PIN, LOW);
                ledsObj.turnOnAllLeds();
                pinball_state = PINBALL_LEDS_ON;
                lastMillis = millis();
            }
            break;

        case PINBALL_LEDS_ON:
            ledsObj.blink();
            if ((millis() - lastMillis) >= DOOR_OPEN_TIME_MS) {
                Serial.println("Leds ON, Door closed, Motor ON");
                ledsObj.turnOnAllLeds();
                digitalWrite(DOOR_PIN, HIGH);
                digitalWrite(MOTOR_PIN, MOTOR_ON);
                pinball_state = PINBALL_COUNT_DOWN;
            }
            break;

        case PINBALL_COUNT_DOWN:
            flippers.play();
            if (ledsObj.finishedCountDown()) {
                Serial.println("Count down finished, Blinking one led");
                pinball_state = PINBALL_BLINK;
                lastMillis = millis();
            }
            break;

        case PINBALL_BLINK:
            flippers.play();
            ledsObj.blinkOnlyOneLed();
            if (millis() - lastMillis >= EXTRA_TIME_MS) {
                Serial.println("Game over, Motor off");
                digitalWrite(MOTOR_PIN, MOTOR_OFF);
                ledsObj.turnOff();
                flippers.stop();
                pinball_state = PINBALL_IDLE;
            }
            break;
    }
}
