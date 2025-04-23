#pragma once
#include <Arduino.h>

struct ToolConfig
{
    String type = "room-stat";
    String code;
    String wifi_ssid;
    String wifi_pass;
};
