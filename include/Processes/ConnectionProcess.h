#pragma once
#include <DTO/ToolConfig.h>
#include <Storage/ToolPreferences.h>
#include <Services/NetworkService.h>
#include <App/State.h>

class ConnectionProcess
{
private:
    NetworkService& network;
    ToolPreferences& preferences;
    DisplayManager& display;
public:
    ConnectionProcess(NetworkService& network, DisplayManager& display, ToolPreferences& preferences);
    void handle();
};
