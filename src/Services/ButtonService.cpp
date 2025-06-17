#include <Services/ButtonService.h>

ButtonService::ButtonService(uint8_t pin): buttonPin(pin) {}

void ButtonService::begin(){
    pinMode(buttonPin, INPUT_PULLUP);
}

void ButtonService::update(){

}

void ButtonService::reset(){

}

void ButtonService::sleep(){

}