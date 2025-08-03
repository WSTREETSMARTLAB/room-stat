#include <Services/LDRService.h>

#define LDR_PIN 34

int LDRService::read(){
    int raw = analogRead(LDR_PIN);
    float percent = ((4095 - raw) / 4095.0) * 99 + 1;
    
    return percent;
}