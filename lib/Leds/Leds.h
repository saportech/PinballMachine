#ifndef LEDS_H
#define LEDS_H

#include <Arduino.h>

#define NO_OF_LEDS 4
#define LED_BLINK_TIME_MS 500
#define GAME_TIME_MS 90000

class Leds {
public:
    void init();
    void blink();
    void blinkOnlyOneLed();
    void turnOff();
    bool finishedCountDown();
    void turnOnAllLeds();
private:
    int led[NO_OF_LEDS] = {16, 17, 18, 19};
};

#endif // LEDS_H
