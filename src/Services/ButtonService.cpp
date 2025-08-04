#include <Services/ButtonService.h>
#include <Managers/PowerManager.h>
#include <Storage/ToolPreferences.h>

extern PowerManager powerManager;

ButtonService::ButtonService(uint8_t pin): buttonPin(pin) {}

void ButtonService::begin(){
    pinMode(buttonPin, INPUT_PULLUP);
}

void ButtonService::update(){
    bool currentState = digitalRead(buttonPin) == LOW;

    if (currentState && !isPressed) {
        isPressed = true;
        pressStartTime = millis();
    } 
    
    if (!currentState && isPressed) {
        unsigned long pressDuration = millis() - pressStartTime;

        if (pressDuration >= 3000) {
            performReset();
        } 
        
        if (pressDuration <= 1000) {
            toggleSleepMode();
        }

        isPressed = false;
    }
}

void ButtonService::performReset(){
    ToolPreferences::reset();
    ESP.restart();
}

void ButtonService::toggleSleepMode(){
    if (powerManager.getCurrentState() == ACTIVE) {
        powerManager.enterSleepMode();
    } else {
        powerManager.wakeUp();
    }
}