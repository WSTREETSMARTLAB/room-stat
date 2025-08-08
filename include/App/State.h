#pragma once
#include <Arduino.h>
#include <Enum/DeviceState.h>

extern bool serverAlive;
extern String token;
extern String serverUrl;
extern DeviceState deviceState;
extern NetworkState networkState;
extern unsigned long lastActivityTime;
extern unsigned long sleepModeStartTime;