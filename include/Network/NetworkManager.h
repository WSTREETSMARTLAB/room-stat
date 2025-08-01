#pragma once
#include <WiFi.h>
#include <Enum/NetworkState.h>

class NetworkManager
{
private:
    NetworkState state;
    unsigned long stateStart;
    unsigned long lastCheck;

    const unsigned long CONNECTION_TIMEOUT = 15000;
    const unsigned long AP_TIMEOUT = 300000;
    const unsigned long CHECK_INTERVAL = 5000;
    const unsigned long RECONNECT_TIMEOUT = 30000;
    const int MAX_RECONNECTION_ATTEMPTS = 3;
public:
    NetworkManager();
    void update();
    void attemptConnection(const String& ssid, const String& password);
    void startAP();
    void forceReconnection();
    void reset();
};


