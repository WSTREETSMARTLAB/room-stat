#pragma once
#include <WebServer.h>
#include <Preferences.h>

class AccessPointManager
{
private:
    static void handleRoot();
    static void handleSubmit();
    static WebServer* _server;
    static Preferences* _preferences;
public:
    AccessPointManager(WebServer& server, Preferences& preferences);
    void begin(String ssid, String password);
};
