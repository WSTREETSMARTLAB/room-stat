#pragma once
#include <DTO/ToolConfig.h>
#include <Storage/ToolPreferences.h>
#include <Services/NetworkService.h>
#include <Services/DisplayService.h>

class ConnectionProcess
{
private:
    NetworkService& network;
    ToolPreferences& preferences;

    bool initialConnectionAttempted;
    unsigned long lastConfigCheck;
public:
    ConnectionProcess(NetworkService& network, ToolPreferences& preferences);
    void handle();
};
