#include <Services/ToolService.h>

ToolService::ToolService(PowerManager& power, DisplayManager& display, WiFiPointManager& wifi): 
power(power),
display(display),
wifi(wifi)
{}

void ToolService::updateActivityMode(unsigned long currentTime){
    DeviceState state = power.getCurrentState();

    power.update(currentTime);

    if (state == power.getCurrentState()){
        return;
    }

    if (power.getCurrentState() == SLEEP){
        display.message("SLEEP", 2000);
        display.turnOff();
    }

    if (power.getCurrentState() == ACTIVE){
        display.turnOn();
        display.message("WAKE UP", 2000);
    }
}