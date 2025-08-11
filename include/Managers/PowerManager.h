#pragma once
#include <Arduino.h>
#include <esp_sleep.h>
#include <esp_pm.h>

class PowerManager
{
private:
    const unsigned long SLEEP_TIMEOUT = 30000;
    const unsigned long ACTIVE_INTERVAL = 15000;
    const unsigned long SLEEP_INTERVAL = 180000;
public:
    PowerManager();
    void update(unsigned long currentTime);
    void enterSleepMode(unsigned long currentTime);
    void sleep();
    void enterActiveMode(unsigned long currentTime);
    void wakeUp();

    unsigned long getInterval() const;
    unsigned long getTimeout() const;

    void setupWakeUpSource();
};
