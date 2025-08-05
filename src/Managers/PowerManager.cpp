#include <Managers/PowerManager.h>

PowerManager::PowerManager(): 
currentState(DeviceState::ACTIVE),
lastActivityTime(millis()),
sleepModeStartTime(0)
{}

void PowerManager::updateActivity(){
    lastActivityTime = millis();
    if (currentState == SLEEP) {
        wakeUp();
    }
}

void PowerManager::transitionToSleep() {
    if (currentState == ACTIVE && 
        (millis() - lastActivityTime) > SLEEP_TIMEOUT) {
        enterSleepMode();
    }
}

void PowerManager::enterSleepMode() {
    currentState = DeviceState::SLEEP;
    setCpuFrequencyMhz(80);
    esp_light_sleep_start();

    // Отключить неиспользуемые GPIO
    // pinMode(unusedPin, INPUT); // Высокий импеданс
    sleepModeStartTime = millis();
}

void PowerManager::wakeUp(){
    currentState = DeviceState::ACTIVE;
    lastActivityTime = millis();
    sleepModeStartTime = 0;
}

bool PowerManager::shouldProcessData() {
    if (currentState == ACTIVE) {
        return true;
    } else if (currentState == SLEEP) {
        return (millis() - sleepModeStartTime) % SLEEP_INTERVAL < 2000;
    }
    return false;
}

DeviceState PowerManager::getCurrentState() {
    return currentState;
}

bool PowerManager::isActive() {
    return currentState == ACTIVE;
}

bool PowerManager::isSleep() {
    return currentState == SLEEP;
}

void PowerManager::setupWakeUpSource(){
    esp_sleep_enable_ext0_wakeup((gpio_num_t)Pin::RESET_BUTTON, 0);
    esp_sleep_enable_timer_wakeup(SLEEP_INTERVAL * 1000);
}