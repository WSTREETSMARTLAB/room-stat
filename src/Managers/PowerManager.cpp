#include <Managers/PowerManager.h>
#include <Enum/IoNumber.h>

PowerManager::PowerManager(): 
currentState(DeviceState::ACTIVE),
lastActivityTime(millis()),
sleepModeStartTime(0)
{}

void PowerManager::enterSleepMode(unsigned long currentTime) {
    currentState = DeviceState::SLEEP;
    sleepModeStartTime = currentTime;
    
    // Вызываем функцию перехода в сон
    sleep();
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
    // Определяем причину пробуждения
    last_wakeup_reason = esp_sleep_get_wakeup_cause();
    
    // Восстанавливаем частоту CPU
    setCpuFrequencyMhz(240);
    
    // Восстанавливаем конфигурацию пинов сенсоров
    pinMode(IoNumber::PIN_DHT22, INPUT_PULLUP);
    pinMode(IoNumber::PIN_LDR, INPUT_PULLUP);
    
    // Небольшая задержка для стабилизации
    delay(50);
    
    // Переключаем состояние в ACTIVE
    currentState = DeviceState::ACTIVE;
    lastActivityTime = millis();
    sleepModeStartTime = 0;
    
    // Логируем причину пробуждения
    switch(last_wakeup_reason) {
        case ESP_SLEEP_WAKEUP_EXT0:
            // Пробуждение по кнопке
            break;
        case ESP_SLEEP_WAKEUP_TIMER:
            // Пробуждение по таймеру
            break;
        default:
            // Другие причины
            break;
    }
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

esp_sleep_wakeup_cause_t PowerManager::getWakeupReason() const {
    return last_wakeup_reason;
}

bool PowerManager::isWakeupByButton() const {
    return last_wakeup_reason == ESP_SLEEP_WAKEUP_EXT0;
}

bool PowerManager::isWakeupByTimer() const {
    return last_wakeup_reason == ESP_SLEEP_WAKEUP_TIMER;
}