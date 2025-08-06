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
    void updateActivity();
    void transitionToSleep();
    void enterSleepMode();
    void wakeUp();
    bool shouldUpdateData();
    bool shouldTransmitData();
    bool shouldDisplayData();
    DeviceState getCurrentState();
    bool isActive();
    bool isSleep();

    void setupWakeUpSource();
};
