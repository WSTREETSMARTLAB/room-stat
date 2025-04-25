#pragma once
#include <WiFi.h>

class WiFiPointManager
{
private:
    String _ssid;
    String _password;
public:
    void connect(const String ssid, const String password);
    bool isConnected() const;
    IPAddress getIP() const;
};
