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
#include <Services/ToolService.h>
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
NetworkService network(wifiPoint, accessPoint);
ResetButtonService resetBtn(power, wifiPoint, display);
ToolService tool(power, display, wifiPoint);
ConnectionProcess connection(network, display, preferences);
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

    display.message("Ready!", 2000);
}

void App::loop(){
    unsigned long currentTime = millis();

    tool.transitionToDataUpdate(currentTime);

    resetBtn.update(currentTime);
    network.update(currentTime);
    server.handleClient();

    if (currentTime - lastDataUpdate >= power.getInterval()){
        data = dataCollecting.handle();

        if (power.getCurrentState() == ACTIVE){
            vizualization.handle(data);
        }

        if (network.getCurrentState() == NetworkState::CONNECTED){
            transmit.handle(data);
        }
        
        lastDataUpdate = currentTime;
    }

    tool.transitionToSleep(currentTime);
}
