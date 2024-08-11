#include "Leds.h"

void Leds::init() {
    for (int i = 0; i < NO_OF_LEDS; i++) {
        pinMode(led[i], OUTPUT);
        digitalWrite(led[i], LOW);
    }
}

void Leds::blink() {
    static unsigned long lastBlinkTime = 0;
    static bool ledState = false;

    if (millis() - lastBlinkTime >= LED_BLINK_TIME_MS) {
        lastBlinkTime = millis();
        ledState = !ledState;

        for (int i = 0; i < NO_OF_LEDS; i++) {
            digitalWrite(led[i], ledState ? HIGH : LOW);
        }
    }
}

void Leds::blinkOnlyOneLed() {
    static unsigned long lastBlinkTime = 0;
    static bool ledState = false;

    if (millis() - lastBlinkTime >= LED_BLINK_TIME_MS) {
        lastBlinkTime = millis();
        ledState = !ledState;

        digitalWrite(led[0], ledState ? HIGH : LOW);
    }
}

void Leds::turnOnAllLeds() {
    for (int i = 0; i < NO_OF_LEDS; i++) {
        digitalWrite(led[i], HIGH);
    }
}

void Leds::turnOff() {
    for (int i = 0; i < NO_OF_LEDS; i++) {
        digitalWrite(led[i], LOW);
    }
}

bool Leds::finishedCountDown() {
    static unsigned long countdown_start = 0;
    static int current_led = NO_OF_LEDS - 1;

    // Initialize countdown_start and turn on all LEDs at the first call
    if (countdown_start == 0) {
        countdown_start = millis();
        for (int i = 0; i < NO_OF_LEDS; i++) {
            digitalWrite(led[i], HIGH);
        }
    }

    // Calculate the time interval for each LED to turn off
    unsigned long interval = GAME_TIME_MS / NO_OF_LEDS;

    // Turn off LEDs one by one based on the interval
    if (millis() - countdown_start >= interval * (NO_OF_LEDS - current_led)) {
        digitalWrite(led[current_led], LOW);
        current_led--;
    }

    // Check if all LEDs are turned off
    if (current_led < 0) {
        // Reset for the next countdown
        countdown_start = 0;
        current_led = NO_OF_LEDS - 1;
        return true;
    }

    return false;
}
