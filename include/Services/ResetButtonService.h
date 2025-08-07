#pragma once
#include <Arduino.h>
#include <Managers/PowerManager.h>
#include <Managers/WiFiPointManager.h>
#include <Managers/DisplayManager.h>

class ResetButtonService
{
private:
    PowerManager& power;
    WiFiPointManager& wifi;
    DisplayManager& display;
    unsigned long pressStartTime;
    bool isPressed = false;

    void performReset();
    void toggleSleepMode();
public:
    ResetButtonService(PowerManager& power, WiFiPointManager& wifi, DisplayManager& display);
    void begin();
    void update(unsigned long currentTime);
};

