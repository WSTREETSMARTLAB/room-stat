#include <Managers/PowerManager.h>
#include <Enum/IoNumber.h>
#include <Enum/DeviceState.h>
#include <App/State.h>

PowerManager::PowerManager(){}

void PowerManager::update(unsigned long currentTime) {
    esp_sleep_wakeup_cause_t currentWakeCause = esp_sleep_get_wakeup_cause();
    
    if (currentWakeCause != wakeCause) {
        wakeCause = currentWakeCause;

        if (currentWakeCause == ESP_SLEEP_WAKEUP_EXT0){
            if (deviceState == SLEEP) {
                enterActiveMode(currentTime);
            }
        }
    }

    if (currentTime - lastActivity >= SLEEP_TIMEOUT){
        enterSleepMode(currentTime);
    }

    if (deviceState == ACTIVE && wakeCause != ESP_SLEEP_WAKEUP_UNDEFINED) {
        resetWakeCause();
    }
}

void PowerManager::enterSleepMode(unsigned long currentTime) {
    if (deviceState != SLEEP){
        deviceState = SLEEP;
        sleepModeStartTime = currentTime;
        resetWakeCause();
    }
}

void PowerManager::sleep(){
    setCpuFrequencyMhz(80);
    esp_light_sleep_start();
}

void PowerManager::enterActiveMode(unsigned long currentTime) {
    if (deviceState != ACTIVE){
        deviceState = ACTIVE;
        sleepModeStartTime = 0;
        lastActivity = currentTime;
        resetWakeCause();
    }
}

void PowerManager::wakeUp(){
    setCpuFrequencyMhz(240);
    delay(50);
}

unsigned long PowerManager::getInterval() const {
    if (deviceState == SLEEP){
        return SLEEP_INTERVAL;
    }
    
    return ACTIVE_INTERVAL;
}

unsigned long PowerManager::getTimeout() const {
    return SLEEP_TIMEOUT;
}

unsigned long PowerManager::getSleepActivityInterval() const {    
    return SLEEP_ACTIVITY_INTERVAL;
}

unsigned long PowerManager::getDataTransmittingDelay() const {    
    if (deviceState == SLEEP){
        return SLEEP_INTERVAL - SLEEP_ACTIVITY_INTERVAL;
    }

    return ACTIVE_INTERVAL;
}

void PowerManager::setupWakeUpSource(){
    esp_sleep_enable_ext0_wakeup((gpio_num_t)IoNumber::PIN_RESET_BUTTON, 0);
    esp_sleep_enable_timer_wakeup(SLEEP_INTERVAL * 1000);
}

void PowerManager::resetWakeCause(){
    wakeCause = ESP_SLEEP_WAKEUP_UNDEFINED;
}
