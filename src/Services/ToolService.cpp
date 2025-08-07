#include <Services/ToolService.h>

ToolService::ToolService(PowerManager& power, DisplayManager& display, WiFiPointManager& wifi): 
power(power),
display(display),
wifi(wifi)
{}

void ToolService::transitionToSleep(unsigned long currentTime){
    power.update(currentTime);

    if (power.getCurrentState() == SLEEP){
        display.message("SLEEP", 2000);
        display.turnOff();
        wifi.disconnect();
        power.sleep(currentTime);
    }
}

void ToolService::transitionToDataUpdate(unsigned long currentTime){
    if (power.getCurrentState() == SLEEP && currentTime - power.getSleepModeStartTime() >= power.getInterval()){
        power.wakeUp(currentTime);
    }
}