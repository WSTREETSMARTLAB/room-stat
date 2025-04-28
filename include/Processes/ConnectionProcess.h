#pragma once
#include <Network/AccessPointManager.h>
#include <Network/WiFiPointManager.h>
#include <DTO/ToolConfig.h>
#include <Storage/ToolPreferences.h>

class ConnectionProcess
{
private:
    AccessPointManager& accessPointManager;
    WiFiPointManager& wifiPointManager;
    ToolPreferences& preferences;
    const String ssid;
    const String pass;
public:
    ConnectionProcess(AccessPointManager& accessPointManager, WiFiPointManager& wiFiPointManager, ToolPreferences& preferences);
    void handle();
};
