#pragma once
#include <WiFi.h>
#include <Services/DisplayService.h>

class WiFiPointManager
{
private:
    String _ssid;
    String _password;
    DisplayService& display;
public:
    WiFiPointManager(DisplayService& display);
    bool connect(const String ssid, const String password);
    static bool isConnected();
    IPAddress getIP() const;
};
