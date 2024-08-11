#ifndef FLIPPERS_H
#define FLIPPERS_H

#include <Arduino.h>

#define NO_OF_CONTROLS 6
#define FLIPPER_STRENGTH 160

class Flippers {
public:
    void init();
    void play();
    void stop();
    void testFlippers();
private:
    int button[NO_OF_CONTROLS] = {33, 32, 35, 39, 12, 36};
    int flipper[NO_OF_CONTROLS] = {21, 22, 23, 25, 26, 27};
};

#endif // FLIPPERS_H
