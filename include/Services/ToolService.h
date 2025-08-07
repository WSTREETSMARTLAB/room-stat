#pragma once
#include <Managers/PowerManager.h>
#include <Managers/DisplayManager.h>
#include <Managers/WiFiPointManager.h>

class ToolService
{
private:
    PowerManager& power;
    DisplayManager& display;
    WiFiPointManager& wifi;
public:
    ToolService(PowerManager& power, DisplayManager& display, WiFiPointManager& wifi);
    void updateActivityMode(unsigned long currentTime);
};
