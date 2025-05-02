#pragma once
#include <WebServer.h>
#include <Preferences.h>
#include <Services/DisplayService.h>

class AccessPointManager
{
private:
    static void handleRoot();
    static void handleSubmit();
    static void handleReboot();
    static WebServer* _server;
    DisplayService& display;
public:
    AccessPointManager(WebServer& server, DisplayService& display);
    void begin(String ssid, String password);
};
