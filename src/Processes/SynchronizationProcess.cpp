#include <Processes/SynchronizationProcess.h>

SynchronizationProcess::SynchronizationProcess(
    PowerManager& power, 
    NetworkService& network, 
    ResetButtonService& resetBtn):
power(power),
network(network),
resetBtn(resetBtn)
{}

void SynchronizationProcess::handle(unsigned long currentTime){
    power.update(currentTime);
    resetBtn.update(currentTime);
    network.update(currentTime);

    if (deviceState == SLEEP){
        
    }
}