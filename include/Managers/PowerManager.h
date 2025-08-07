#pragma once
#include <Arduino.h>
#include <Enum/DeviceState.h>
#include <esp_sleep.h>
#include <esp_pm.h>

class PowerManager
{
private:
    DeviceState currentState;
    unsigned long lastActivityTime;
    unsigned long sleepModeStartTime;
    unsigned long lastDataUpdate;
    unsigned long lastDataTransmit;

    const unsigned long ACTIVE_INTERVAL = 3000;

    const unsigned long SLEEP_TIMEOUT = 30000;
    const unsigned long SLEEP_INTERVAL = 180000;
public:
    PowerManager();
    void enterSleepMode(unsigned long currentTime);
    void sleep();
    void enterActiveMode(unsigned long currentTime);
    void wakeUp();

    DeviceState getCurrentState();
    unsigned long getInterval() const;

    void setupWakeUpSource();
};
