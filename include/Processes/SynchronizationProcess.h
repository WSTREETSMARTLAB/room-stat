#pragma once
#include <App/State.h>
#include <Managers/PowerManager.h>
#include <Services/NetworkService.h>
#include <Services/ResetButtonService.h>

class SynchronizationProcess
{
private:
    PowerManager& power;
    NetworkService& network;
    ResetButtonService& resetBtn;
public:
    SynchronizationProcess(PowerManager& power, NetworkService& network, ResetButtonService& resetBtn);
    void handle(unsigned long currentTime);
};
