#include <Services/ResetButtonService.h>
#include <Managers/PowerManager.h>
#include <Storage/ToolPreferences.h>
#include <Enum/IoNumber.h>

ResetButtonService::ResetButtonService(PowerManager& power, WiFiPointManager& wifi, DisplayManager& display): 
power(power),
wifi(wifi),
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
            if (power.getCurrentState() == ACTIVE){
                power.enterSleepMode(pressStartTime);
                display.turnOff();
                power.sleep();
            }
        }

        isPressed = false;
    }
}

void ResetButtonService::performReset(){
    ToolPreferences::reset();
    ESP.restart();
}