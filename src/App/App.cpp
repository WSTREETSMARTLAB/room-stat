#include <App/App.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Storage/ToolPreferences.h>
#include <Network/AccessPointManager.h>
#include <Network/WiFiPointManager.h>
#include <DTO/ToolConfig.h>
#include <Services/ApiService.h>
#include <Services/DHTService.h>
#include <Services/LDRService.h>
#include <Services/DisplayService.h>
#include <Processes/AuthProcess.h>
#include <Processes/ConnectionProcess.h>
#include <Processes/DataCollectingProcess.h>
#include <DTO/DataConfig.h>
#include <Processes/HealthCheckProcess.h>
#include <Processes/VizualizationDataProcess.h>
#include <Processes/TransmitDataProcess.h>

WebServer server(80);
DHTService dht;
LDRService ldr;
ApiService api;
DisplayService display;
AccessPointManager accessPointManager(server, display);
WiFiPointManager wifiPointManager(display);
ToolPreferences preferences;
HealthCheckProcess healthCheck(api, display);
NetworkService network(wifiPointManager, accessPointManager);
ConnectionProcess connection(network, preferences);
AuthProcess auth(api, preferences, display);
DataCollectingProcess dataCollecting(dht, ldr);
VizualizationDataProcess vizualization(display);
TransmitDataProcess transmit(api);
DataConfig data;

void App::setup(){
    display.begin();
    display.message("Setup", 2000);

    dht.begin();
    connection.handle();
    healthCheck.handle();
    auth.handle();

    display.message("Ready!", 3000);
}

void App::loop(){
    server.handleClient();

    data = dataCollecting.handle();

    if (!WiFiPointManager::isConnected()){
        connection.handle();
    }

    transmit.handle(data);
    vizualization.handle(data);
}