#include <Services/LDRService.h>
#include <Enum/Pin.h>

int LDRService::read(){
    int raw = analogRead(Pin::LDR);
    float percent = ((4095 - raw) / 4095.0) * 99 + 1;
    
    return percent;
}