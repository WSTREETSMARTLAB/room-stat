#include <Managers/PowerManager.h>
#include <Enum/IoNumber.h>
#include <Enum/DeviceState.h>
#include <App/State.h>

PowerManager::PowerManager(){}

void PowerManager::update(unsigned long currentTime) {
    if (currentTime - lastActivity >= SLEEP_TIMEOUT){
        Serial.println("SLEEP TIMEOUT: " + String(currentTime));
        enterSleepMode(currentTime);
        Serial.println(deviceState == ACTIVE ? "toggled to ACTIVE" : "toggled to SLEEP");
        delay(50);
    }

    if(esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0){
        enterActiveMode(currentTime);
    }
}

void PowerManager::enterSleepMode(unsigned long currentTime) {
    deviceState = SLEEP;
    sleepModeStartTime = currentTime;
}

void PowerManager::sleep(){
    Serial.println("TURN TO SLEEP");
    setCpuFrequencyMhz(80);
    esp_light_sleep_start();
}

void PowerManager::enterActiveMode(unsigned long currentTime) {
    deviceState = ACTIVE;
    sleepModeStartTime = 0;
}

void PowerManager::wakeUp(){
    setCpuFrequencyMhz(240);
    Serial.println("WAKED UP");
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