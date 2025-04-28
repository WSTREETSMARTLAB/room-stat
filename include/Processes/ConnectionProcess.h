#pragma once
#include <Network/AccessPointManager.h>
#include <Network/WiFiPointManager.h>
#include <DTO/ToolConfig.h>
#include <Storage/ToolPreferences.h>
#include <Services/DisplayService.h>

class ConnectionProcess
{
private:
    DisplayService& display; 
    AccessPointManager& accessPointManager;
    WiFiPointManager& wifiPointManager;
    ToolConfig config;
    const String ssid;
    const String pass;
public:
    ConnectionProcess(AccessPointManager& accessPointManager, WiFiPointManager& wiFiPointManager, DisplayService& display);
    void handle();
};
