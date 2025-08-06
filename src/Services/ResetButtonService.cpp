#include <Services/ResetButtonService.h>
#include <Managers/PowerManager.h>
#include <Storage/ToolPreferences.h>
#include <Enum/IoNumber.h>

ResetButtonService::ResetButtonService(PowerManager& power, DisplayManager& display): 
power(power),
display(display)
{}

void ResetButtonService::begin(){
    pinMode(IoNumber::PIN_RESET_BUTTON, INPUT_PULLUP);
    power.setupWakeUpSource();
}

void ResetButtonService::update(unsigned long currentTime){
    bool currentState = digitalRead(IoNumber::PIN_RESET_BUTTON) == LOW;

    if (currentState && !isPressed) {
        isPressed = true;
        pressStartTime = currentTime;
    } 
    
    if (!currentState && isPressed) {
        unsigned long pressDuration = currentTime - pressStartTime;

        if (pressDuration >= 3000) {
            display.message("reset", 3000);
            // performReset();
        } 
        
        if (pressDuration <= 1000) {
            toggleSleepMode();
        }

        isPressed = false;
    }
}

void ResetButtonService::performReset(){
    ToolPreferences::reset();
    ESP.restart();
}

void ResetButtonService::toggleSleepMode(){
    if (power.getCurrentState() == ACTIVE) {
        display.turnOff();
        // switch off wi-fi
        power.enterSleepMode(pressStartTime);
    } else {
        display.turnOn();
        power.enterActiveMode(pressStartTime);
        // connect to wi-fi
    }
}