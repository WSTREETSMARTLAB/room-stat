#pragma once
#include <App/State.h>
#include <Managers/PowerManager.h>

class SynchronizationProcess
{
private:
    PowerManager& power;
public:
    SynchronizationProcess(PowerManager& power);
    void handle(unsigned long currentTime);
};
