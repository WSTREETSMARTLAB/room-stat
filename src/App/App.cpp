#include <App/App.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Storage/ToolPreferences.h>
#include <Managers/DisplayManager.h>
#include <Managers/AccessPointManager.h>
#include <Managers/WiFiPointManager.h>
#include <Managers/PowerManager.h>
#include <DTO/ToolConfig.h>
#include <Services/ApiService.h>
#include <Services/DHTService.h>
#include <Services/LDRService.h>
#include <Services/ResetButtonService.h>
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
DisplayManager display;
AccessPointManager accessPointManager(server);
WiFiPointManager wifiPointManager;
PowerManager power;
ToolPreferences preferences;
HealthCheckProcess healthCheck(api, display);
NetworkService network(wifiPointManager, accessPointManager);
ResetButtonService resetBtn(power);
ConnectionProcess connection(network, preferences);
AuthProcess auth(api, preferences, display);
DataCollectingProcess dataCollecting(dht, ldr);
VizualizationDataProcess vizualization(display);
TransmitDataProcess transmit(api);
DataConfig data;

void App::setup(){
    display.begin();
    display.message("Setup", 2000);

    resetBtn.begin();
    dht.begin();
    connection.handle();
    healthCheck.handle();
    auth.handle();

    display.message("Ready!", 3000);
}

void App::loop(){
    server.handleClient();

    data = dataCollecting.handle();
    connection.handle();
    transmit.handle(data);
    vizualization.handle(data);
}