#pragma once
#include <Arduino.h>
#include <Enum/DeviceState.h>

class PowerManager
{
private:
    DeviceState currentState;

public:
    PowerManager();

};
