#pragma once
#include <Arduino.h>
#include <App/State.h>
#include <esp_sleep.h>
#include <esp_pm.h>

class PowerManager
{
private:
    unsigned long lastDataUpdate;
    unsigned long lastDataTransmit;

    const unsigned long ACTIVE_INTERVAL = 3000;
    const unsigned long SLEEP_TIMEOUT = 30000;
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
