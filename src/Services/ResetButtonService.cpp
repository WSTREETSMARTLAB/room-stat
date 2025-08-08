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
    bool btnState = digitalRead(IoNumber::PIN_RESET_BUTTON) == LOW;

    if (btnState && !isPressed) {
        isPressed = true;
        pressStartTime = currentTime;
    } 
    
    if (!btnState && isPressed) {
        unsigned long pressDuration = currentTime - pressStartTime;

        if (pressDuration >= 3000) {
            display.message("reset", 3000);
            // performReset();
        } 
        
        if (pressDuration <= 1000) {
            if (deviceState == ACTIVE){
                power.enterSleepMode(pressStartTime);
                display.turnOff();
            }
        }

        isPressed = false;
    }
}

void ResetButtonService::performReset(){
    ToolPreferences::reset();
    ESP.restart();
}