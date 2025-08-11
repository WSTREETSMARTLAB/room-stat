#include <Services/LDRService.h>
#include <Enum/IoNumber.h>

int LDRService::read(){
    int raw = analogRead(IoNumber::PIN_LDR);
    float percent = ((4095 - raw) / 4095.0) * 99 + 1;
    
    return percent;
}