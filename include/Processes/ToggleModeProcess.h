#pragma once
#include <Managers/PowerManager.h>
#include <Managers/DisplayManager.h>
#include <App/State.h>

class ToggleModeProcess
{
private:
    PowerManager& power;
    DisplayManager& display;
public:
    ToggleModeProcess(PowerManager& power, DisplayManager& display);
    void handle(unsigned long currentTime);
};
