#pragma once
#include <Arduino.h>

class ButtonService
{
private:
    const uint8_t buttonPin;
    unsigned long pressStartTime = 0;
    bool isPressed = false;

    void performReset();
    void toggleSleepMode();
public:
    ButtonService(uint8_t buttonPin);
    void begin();
    void update();
};

