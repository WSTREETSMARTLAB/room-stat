#pragma once
#include <Arduino.h>
#include <esp_sleep.h>
#include <esp_pm.h>

class PowerManager
{
private:
    const unsigned long SLEEP_TIMEOUT = 30000;
    const unsigned long ACTIVE_INTERVAL = 15000;
    const unsigned long SLEEP_INTERVAL = 60000;

    esp_sleep_wakeup_cause_t wakeCause = ESP_SLEEP_WAKEUP_UNDEFINED;
    void resetWakeCause();
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
