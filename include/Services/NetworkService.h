#pragma once
#include <WiFi.h>
#include <Enum/NetworkState.h>
#include <Managers/WiFiPointManager.h>
#include <Managers/AccessPointManager.h>

class NetworkService
{
private:
    NetworkState state;
    WiFiPointManager& wifi;
    AccessPointManager& accessPoint;
    unsigned long stateStart;
    unsigned long lastCheck;

    const unsigned long CONNECTION_TIMEOUT = 15000;
    const unsigned long AP_TIMEOUT = 300000;
    const unsigned long CHECK_INTERVAL = 5000;
    const unsigned long RECONNECT_TIMEOUT = 30000;
    const int MAX_RECONNECTION_ATTEMPTS = 3;

    int reconnectionAttempts;
    int totalConnectionAttempts;
    int successfulConnections;
    unsigned long lastSuccessfulConnection;

    void evaluateState();
    void transitionTo(NetworkState newState);
    void updateMetrics(bool connectionSuccess);
public:
    NetworkService(WiFiPointManager& wifi, AccessPointManager& accessPoint);
    void update();
    void attemptConnection(const String& ssid, const String& password);
    void startAP();
    void forceReconnection();
    void reset();

    unsigned long getTimeInCurrentState() const;
    NetworkState getCurrentState() const;
};


