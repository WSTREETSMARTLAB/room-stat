#include <Managers/PowerManager.h>
#include <Enum/IoNumber.h>

PowerManager::PowerManager(): 
currentState(DeviceState::ACTIVE),
lastActivityTime(millis()),
sleepModeStartTime(0)
{}

void PowerManager::enterSleepMode(unsigned long currentTime) {
    currentState = DeviceState::SLEEP;
    sleepModeStartTime = millis();

    // pinMode(IoNumber::PIN_DHT22, INPUT);
    // pinMode(IoNumber::PIN_LDR, INPUT);

    // setCpuFrequencyMhz(80);
    // esp_light_sleep_start();
}

void PowerManager::enterActiveMode(unsigned long currentTime) {
    currentState = DeviceState::ACTIVE;
    lastActivityTime = currentTime;

    sleepModeStartTime = 0;
}

void PowerManager::wakeUp(){
    // pinMode(IoNumber::PIN_DHT22, INPUT_PULLUP);
    // pinMode(IoNumber::PIN_LDR, INPUT_PULLUP);

    // setCpuFrequencyMhz(240);

    // delay(50);
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

void PowerManager::setupWakeUpSource(){
    esp_sleep_enable_ext0_wakeup((gpio_num_t)IoNumber::PIN_RESET_BUTTON, 0);
    esp_sleep_enable_timer_wakeup(SLEEP_INTERVAL * 1000);
}