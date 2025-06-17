#pragma once
#include <Arduino.h>

class ButtonService
{
private:
    const uint8_t buttonPin;
    unsigned long pressStartTime = 0;
    bool isPressed = false;

    void reset();
    void sleep();
public:
    ButtonService(uint8_t buttonPin);
    void begin();
    void update();
};

