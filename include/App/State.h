#pragma once
#include <Arduino.h>
#include <Enum/DeviceState.h>

extern bool serverAlive;
extern String token;
extern String serverUrl;
extern DeviceState currentDeviceState;
extern unsigned long lastActivityTime;
extern unsigned long sleepModeStartTime;