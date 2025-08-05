#pragma once
#include <Arduino.h>
#include <Managers/PowerManager.h>
#include <Enum/Pin.h>

class ResetButtonService
{
private:
    PowerManager power;
    unsigned long pressStartTime = 0;
    bool isPressed = false;

    void performReset();
    void toggleSleepMode();
public:
    ResetButtonService(PowerManager& power);
    void begin();
    void update();
};

