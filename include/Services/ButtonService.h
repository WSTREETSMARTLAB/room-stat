#pragma once
#include <Arduino.h>
#include <Managers/PowerManager.h>

class ButtonService
{
private:
    PowerManager power;
    static const uint8_t BUTTON_PIN = 13;
    unsigned long pressStartTime = 0;
    bool isPressed = false;

    void performReset();
    void toggleSleepMode();
public:
    ButtonService(PowerManager& power);
    void begin();
    void update();
};

