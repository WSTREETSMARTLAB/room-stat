#include <Services/ToolService.h>

ToolService::ToolService(PowerManager& power, DisplayManager& display, WiFiPointManager& wifi): 
power(power),
display(display),
wifi(wifi)
{}

void ToolService::updateActivityMode(unsigned long currentTime){
    power.update(currentTime);

    if (power.getCurrentState() == SLEEP && power.getSleepModeStartTime() == currentTime){
        display.message("SLEEP", 2000);
        display.turnOff();
        wifi.disconnect();
        power.sleep();
    }

    if (power.getCurrentState() == ACTIVE && power.getLastActivityTime() > currentTime){
        power.wakeUp();
        display.turnOn();
        display.message("WAKE UP", 2000);
    }
}

void ToolService::transitionToDataUpdate(unsigned long currentTime){
    if (power.getCurrentState() == SLEEP && currentTime - power.getSleepModeStartTime() >= power.getInterval()){
        power.wakeUp();
    }
}