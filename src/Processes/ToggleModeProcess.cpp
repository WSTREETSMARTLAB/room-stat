#include <Processes/ToggleModeProcess.h>

ToggleModeProcess::ToggleModeProcess(PowerManager& power, DisplayManager& display): 
power(power),
display(display){}

void ToggleModeProcess::handle(unsigned long currentTime){
    if (deviceState == SLEEP){
        if (sleepModeStartTime == currentTime){
            display.message("SLEEP", 1000);
            display.turnOff();
        }
        
        if (currentTime >= (lastDataUpdate + power.getSleepActivityInterval())){
            power.sleep();
        }
    }

    if ((deviceState == ACTIVE) && (lastActivity == currentTime)){
        power.wakeUp();
        display.turnOn();
        display.message("ACTIVE", 1000);
    }
};