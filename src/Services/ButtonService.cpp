#include <Services/ButtonService.h>

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
        
        if (pressDuration >= 100) {
            toggleSleepMode();
        }

        isPressed = false;
    }
}

void ButtonService::performReset(){

}

void ButtonService::toggleSleepMode(){

}