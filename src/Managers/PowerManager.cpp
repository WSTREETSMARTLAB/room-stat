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
    sleepModeStartTime = millis();
}

void PowerManager::wakeUp(){
    currentState = DeviceState::ACTIVE;
    lastActivityTime = millis();
    sleepModeStartTime = 0;
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