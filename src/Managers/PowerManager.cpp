#include <Managers/PowerManager.h>
#include <Enum/IoNumber.h>
#include <Enum/DeviceState.h>
#include <App/State.h>

PowerManager::PowerManager(){}

void PowerManager::update(unsigned long currentTime) {
    wakeCause = esp_sleep_get_wakeup_cause();

    if (deviceState == ACTIVE && (currentTime - lastActivity >= SLEEP_TIMEOUT)){
        enterSleepMode(currentTime);
    }

    if(wakeCause == ESP_SLEEP_WAKEUP_EXT0){
        enterActiveMode(currentTime);
    }
}

void PowerManager::enterSleepMode(unsigned long currentTime) {
    deviceState = SLEEP;
    sleepModeStartTime = currentTime;
    wakeCause = ESP_SLEEP_WAKEUP_UNDEFINED;
}

void PowerManager::sleep(){
    setupWakeUpSource();
    setCpuFrequencyMhz(80);
    esp_light_sleep_start();
}

void PowerManager::enterActiveMode(unsigned long currentTime) {
    deviceState = ACTIVE;
    sleepModeStartTime = 0;
    wakeCause = ESP_SLEEP_WAKEUP_UNDEFINED;
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

void PowerManager::setupWakeUpSource(){
    esp_sleep_enable_ext0_wakeup((gpio_num_t)IoNumber::PIN_RESET_BUTTON, 0);
    esp_sleep_enable_timer_wakeup(SLEEP_INTERVAL * 1000);
}