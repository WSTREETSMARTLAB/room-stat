#pragma once
#include <Arduino.h>
#include <Enum/NetworkState.h>
#include <Enum/DeviceState.h>

extern bool serverAlive;
extern String token;
extern String serverUrl;
extern DeviceState deviceState;
extern NetworkState networkState;
extern unsigned long sleepModeStartTime;
extern unsigned long lastDataUpdate;