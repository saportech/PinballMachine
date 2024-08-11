#include "Flippers.h"

void Flippers::init() {
    for (int i = 0; i < NO_OF_CONTROLS; i++) {
        pinMode(flipper[i], OUTPUT);
        pinMode(button[i], INPUT_PULLUP);
        digitalWrite(flipper[i], HIGH);
    }
}

void Flippers::testFlippers() {
    static unsigned long lastTestTime = 0;
    static int currentFlipper = 0;

    unsigned long currentTime = millis();

    // Check if 1 second has passed since the last flipper was tested
    if (currentTime - lastTestTime >= 1000) {
        // Turn off the previous flipper
        if (currentFlipper > 0) {
            analogWrite(flipper[currentFlipper - 1], 0);
        } else {
            analogWrite(flipper[NO_OF_CONTROLS - 1], 0);
        }

        // Activate the current flipper
        analogWrite(flipper[currentFlipper], 140);
        delay(1500);  // Keep the flipper activated for 100 milliseconds
        analogWrite(flipper[currentFlipper], 0);

        // Move to the next flipper
        currentFlipper = (currentFlipper + 1) % NO_OF_CONTROLS;
        lastTestTime = currentTime;

        // Print the current flipper being tested
        Serial.print("Testing flipper ");
        Serial.println(currentFlipper + 1);  // Adjust for 1-based indexing in the output
    }
}

void Flippers::stop() {
    for (int i = 0; i < NO_OF_CONTROLS; i++) {
        digitalWrite(flipper[i], HIGH);
    }
}

void Flippers::play() {
    static unsigned long lastPlayTime[NO_OF_CONTROLS] = {0};
    static bool flipperState[NO_OF_CONTROLS] = {false};

    for (int i = 0; i < NO_OF_CONTROLS; i++) {
        if (digitalRead(button[i]) == LOW && !flipperState[i] && millis() - lastPlayTime[i] >= 200) {
            digitalWrite(flipper[i], LOW);
            flipperState[i] = true;
            lastPlayTime[i] = millis();
            Serial.println("Button number " + String(i + 1) + " pressed");
        } else if (flipperState[i] && millis() - lastPlayTime[i] >= 100) {
            digitalWrite(flipper[i], HIGH);
            flipperState[i] = false;
            lastPlayTime[i] = millis();
        }
    }
}
