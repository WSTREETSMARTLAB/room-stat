#include <Processes/SynchronizationProcess.h>

SynchronizationProcess::SynchronizationProcess(PowerManager& power):
power(power)
{}

void SynchronizationProcess::handle(unsigned long currentTime){
    power.update(currentTime);
}