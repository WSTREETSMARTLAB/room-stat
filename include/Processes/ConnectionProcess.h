#pragma once
#include <DTO/ToolConfig.h>
#include <Storage/ToolPreferences.h>
#include <Services/NetworkService.h>

class ConnectionProcess
{
private:
    NetworkService& network;
    ToolPreferences& preferences;

    bool initialConnectionAttempted;
    unsigned long lastConfigCheck;

    void attemptInitialConnection();
    void handleNetworkState();
    bool shouldAttemptReconnection();
public:
    ConnectionProcess(NetworkService& network, ToolPreferences& preferences);
    void handle();
};
