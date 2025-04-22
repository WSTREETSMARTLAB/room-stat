#pragma once
#include <WebServer.h>

class AccessPointManager
{
private:
    static void handleRoot();
    static void handleSubmit();
    static WebServer* _server;
public:
    AccessPointManager(WebServer& server);
    void begin(String ssid, String password);
};
