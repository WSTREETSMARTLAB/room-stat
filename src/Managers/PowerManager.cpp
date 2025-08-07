#include <Managers/PowerManager.h>
#include <Enum/IoNumber.h>

PowerManager::PowerManager(): 
currentState(DeviceState::ACTIVE),
lastActivityTime(millis()),
sleepModeStartTime(0)
{}

void PowerManager::update(unsigned long currentTime) {
    if (currentTime - lastActivityTime >= SLEEP_TIMEOUT){
        Serial.println("sleep timeout");
        enterSleepMode(currentTime);
    }

    if(esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0){
        enterActiveMode(currentTime);
    }
}

void PowerManager::enterSleepMode(unsigned long currentTime) {
    currentState = DeviceState::SLEEP;
    sleepModeStartTime = currentTime;
}

void PowerManager::sleep(){
    pinMode(IoNumber::PIN_DHT22, INPUT);
    pinMode(IoNumber::PIN_LDR, INPUT);

    setCpuFrequencyMhz(80);
    esp_light_sleep_start();
}

void PowerManager::enterActiveMode(unsigned long currentTime) {
    currentState = DeviceState::ACTIVE;
    lastActivityTime = currentTime;
    sleepModeStartTime = 0;
}

void PowerManager::wakeUp(){
    setCpuFrequencyMhz(240);
    
    pinMode(IoNumber::PIN_DHT22, INPUT_PULLUP);
    pinMode(IoNumber::PIN_LDR, INPUT_PULLUP);
    
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

void PowerManager::setupWakeUpSource(){
    esp_sleep_enable_ext0_wakeup((gpio_num_t)IoNumber::PIN_RESET_BUTTON, 0);
    esp_sleep_enable_timer_wakeup(SLEEP_INTERVAL * 1000);
}

unsigned long PowerManager::getSleepModeStartTime() const {
    return sleepModeStartTime;
}

