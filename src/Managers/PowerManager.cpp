#include <Managers/PowerManager.h>
#include <Enum/IoNumber.h>

PowerManager::PowerManager(): 
currentState(DeviceState::ACTIVE),
lastActivityTime(millis()),
sleepModeStartTime(0)
{}

void PowerManager::update(unsigned long currentTime) {
    if (currentTime - lastActivityTime >= SLEEP_TIMEOUT){
        currentState = SLEEP;
    }
}

void PowerManager::enterSleepMode() {
    currentState = DeviceState::SLEEP;
}

void PowerManager::sleep(unsigned long currentTime){
    sleepModeStartTime = currentTime;

    pinMode(IoNumber::PIN_DHT22, INPUT);
    pinMode(IoNumber::PIN_LDR, INPUT);

    setCpuFrequencyMhz(80);
    esp_light_sleep_start();
}

void PowerManager::enterActiveMode() {
    currentState = DeviceState::ACTIVE;
}

void PowerManager::wakeUp(unsigned long currentTime){
    setCpuFrequencyMhz(240);
    
    pinMode(IoNumber::PIN_DHT22, INPUT_PULLUP);
    pinMode(IoNumber::PIN_LDR, INPUT_PULLUP);

    lastActivityTime = currentTime;
    sleepModeStartTime = 0;
    
    delay(50);
}

DeviceState PowerManager::getCurrentState() {
    return currentState;
}

unsigned long PowerManager::getInterval() const {
    if (currentState == SLEEP){
        return SLEEP_INTERVAL;
    }
    
    return ACTIVE_INTERVAL;
}

unsigned long PowerManager::getTimeout() const {
    return SLEEP_TIMEOUT;
}

unsigned long PowerManager::getLastActivityTime() const {
    return lastActivityTime;
}

void PowerManager::setupWakeUpSource(){
    esp_sleep_enable_ext0_wakeup((gpio_num_t)IoNumber::PIN_RESET_BUTTON, 0);
    esp_sleep_enable_timer_wakeup(SLEEP_INTERVAL * 1000);
}