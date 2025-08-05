#pragma once
#include <Arduino.h>

class ButtonService
{
private:
    static const uint8_t BUTTON_PIN = 13;
    unsigned long pressStartTime = 0;
    bool isPressed = false;

    void performReset();
    void toggleSleepMode();
public:
    ButtonService();
    void begin();
    void update();
};

