#include <Processes/ToggleModeProcess.h>

ToggleModeProcess::ToggleModeProcess(PowerManager& power, DisplayManager& display): 
power(power),
display(display){}

void ToggleModeProcess::handle(){
    if (deviceState == SLEEP){
        display.message("SLEEP MODE", 1000);
        display.turnOff();
        power.sleep();
    }

    if (deviceState == ACTIVE){
        power.wakeUp();
        display.turnOn();
        display.message("ACTIVE MODE", 1000);
    }
};