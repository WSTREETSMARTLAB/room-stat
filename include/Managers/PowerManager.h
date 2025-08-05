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
    const unsigned long SLEEP_TIMEOUT = 30000;
    const unsigned long SLEEP_INTERVAL = 180000;
public:
    PowerManager();
    void updateActivity();
    void transitionToSleep();
    void enterSleepMode();
    void wakeUp();
    bool shouldProcessData();
    DeviceState getCurrentState();
    bool isActive();
    bool isSleep();

    void setupWakeUpSource(uint8_t pin);
};
