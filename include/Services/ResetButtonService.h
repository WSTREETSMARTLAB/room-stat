#pragma once
#include <Arduino.h>
#include <Managers/PowerManager.h>
#include <Managers/DisplayManager.h>

class ResetButtonService
{
private:
    PowerManager& power;
    DisplayManager& display;
    unsigned long pressStartTime;
    bool isPressed = false;

    void performReset();
public:
    ResetButtonService(PowerManager& power, DisplayManager& display);
    void begin();
    void update(unsigned long currentTime);
};

