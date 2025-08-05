#pragma once
#include <Arduino.h>
#include <Managers/PowerManager.h>
#include <Managers/DisplayManager.h>

class ResetButtonService
{
private:
    PowerManager& power;
    DisplayManager& display;
    unsigned long pressStartTime = 0;
    bool isPressed = false;

    void performReset();
    void toggleSleepMode();
public:
    ResetButtonService(PowerManager& power, DisplayManager& display);
    void begin();
    void update();
};

