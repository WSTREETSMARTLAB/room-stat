#include <App/App.h>
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
AccessPointManager accessPoint(server);
WiFiPointManager wifiPoint;
PowerManager power;
ToolPreferences preferences;
HealthCheckProcess healthCheck(api, display);
NetworkService network(wifiPoint, accessPoint, display);
ResetButtonService resetBtn(power, display);
ConnectionProcess connection(network, preferences);
AuthProcess auth(api, preferences, display);
DataCollectingProcess dataCollecting(dht, ldr);
VizualizationDataProcess vizualization(display);
TransmitDataProcess transmit(api);
DataConfig data;

void App::setup(){
    display.begin();
    display.message("Setup", 1000);

    resetBtn.begin();
    dht.begin();
    connection.handle();
    healthCheck.handle();
    auth.handle();

    lastDataUpdate = millis();
    lastDataTransmit = millis();

    display.message("Ready!", 2000);
}

void App::loop(){
    unsigned long currentTime = millis();

    resetBtn.update();
    server.handleClient();
    connection.handle();

    if (currentTime - lastDataUpdate >= DATA_UPDATE_INTERVAL){
        data = dataCollecting.handle();
        vizualization.handle(data);
        lastDataUpdate = currentTime; 
    }

    if (currentTime - lastDataTransmit >= DATA_TRANSMIT_INTERVAL && network.getCurrentState() == NetworkState::CONNECTED){
        transmit.handle(data);
        lastDataTransmit = currentTime;
    }
}