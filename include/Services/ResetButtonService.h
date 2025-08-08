#pragma once
#include <Arduino.h>
#include <Managers/PowerManager.h>
#include <Managers/WiFiPointManager.h>
#include <Managers/DisplayManager.h>

class ResetButtonService
{
private:
    PowerManager& power;
    unsigned long pressStartTime;
    bool isPressed = false;

    void performReset();
public:
    ResetButtonService(PowerManager& power);
    void begin();
    void update(unsigned long currentTime);
};

