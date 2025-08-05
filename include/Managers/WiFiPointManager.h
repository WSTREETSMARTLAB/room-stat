#pragma once
#include <WiFi.h>

class WiFiPointManager
{
private:
    String _ssid;
    String _password;
public:
    WiFiPointManager();
    void connect(const String ssid, const String password);
    static bool isConnected();
    IPAddress getIP() const;
};
