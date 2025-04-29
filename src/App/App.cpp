#include <App/App.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Storage/ToolPreferences.h>
#include <Network/AccessPointManager.h>
#include <Network/WiFiPointManager.h>
#include <DTO/ToolConfig.h>
#include <Services/ApiService.h>
#include <Services/DHTService.h>
#include <Services/DisplayService.h>
#include <Processes/AuthProcess.h>
#include <Processes/ConnectionProcess.h>

const char* serverUrl = "http://192.168.0.100:8080";

WebServer server(80);
DHTService dhtService;
ApiService apiService(serverUrl);
DisplayService display;
AccessPointManager accessPointManager(server);
WiFiPointManager wifiPointManager;
ToolPreferences preferences;
ToolConfig config;
AuthProcess auth(apiService, config, display);
ConnectionProcess connection(accessPointManager, wifiPointManager, preferences);

void App::setup(){
    display.begin();
    display.logo(5000);

    connection.handle();
    auth.handle();

    display.message("Ready!", 3000);
}

void App::loop(){
    server.handleClient();
}