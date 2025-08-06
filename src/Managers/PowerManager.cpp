#include <Managers/PowerManager.h>
#include <Enum/IoNumber.h>

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
    sleepModeStartTime = millis();

    // pinMode(IoNumber::PIN_DHT22, INPUT);
    // pinMode(IoNumber::PIN_LDR, INPUT);

    // setCpuFrequencyMhz(80);
    // esp_light_sleep_start();
}

void PowerManager::wakeUp(){
    currentState = DeviceState::ACTIVE;
    lastActivityTime = millis();

    // pinMode(IoNumber::PIN_DHT22, INPUT_PULLUP);
    // pinMode(IoNumber::PIN_LDR, INPUT_PULLUP);

    // setCpuFrequencyMhz(240);

    delay(50);

    sleepModeStartTime = 0;
}

bool PowerManager::shouldUpdateData() {
    unsigned long currentTime = millis();

    if (currentState == ACTIVE) {
        return (currentTime - lastDataUpdate >= ACTIVE_INTERVAL);
    }

    if (currentState == SLEEP){
        return (currentTime - lastDataUpdate >= SLEEP_INTERVAL);
    }
}

bool PowerManager::shouldTransmitData() {
    unsigned long currentTime = millis();

    if (currentState == ACTIVE){
        return true;
    }
    
    if (currentState == SLEEP){
        return shouldUpdateData();
    }
}

bool PowerManager::shouldDisplayData() {
    if (currentState != ACTIVE){
        return false;
    }

    unsigned long currentTime = millis();
    return (currentTime - lastDataUpdate) >= ACTIVE_INTERVAL;
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
    esp_sleep_enable_ext0_wakeup((gpio_num_t)IoNumber::PIN_RESET_BUTTON, 0);
    esp_sleep_enable_timer_wakeup(SLEEP_INTERVAL * 1000);
}