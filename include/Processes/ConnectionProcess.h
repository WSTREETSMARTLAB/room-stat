#pragma once
#include <DTO/ToolConfig.h>
#include <Storage/ToolPreferences.h>
#include <Services/NetworkService.h>

class ConnectionProcess
{
private:
    NetworkService& network;
    ToolPreferences& preferences;
public:
    ConnectionProcess(NetworkService& network, ToolPreferences& preferences);
    void handle();
};
