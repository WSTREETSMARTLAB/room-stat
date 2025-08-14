#include <App/App.h>
#include <App/State.h>
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
#include <Processes/SynchronizationProcess.h>
#include <Processes/HealthCheckProcess.h>
#include <Processes/VizualizationDataProcess.h>
#include <Processes/TransmitDataProcess.h>
#include <Processes/ToggleModeProcess.h>

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
ResetButtonService resetBtn(power, display);
SynchronizationProcess synchronization(power, network, resetBtn);
ConnectionProcess connection(network, display, preferences);
AuthProcess auth(api, preferences, display);
DataCollectingProcess dataCollecting(dht, ldr, power);
VizualizationDataProcess vizualization(display);
TransmitDataProcess transmit(api);
ToggleModeProcess toggleMode(power, display);
DataConfig data;

void App::setup(){
    display.begin();
    display.message("Setup", 1000);

    resetBtn.begin();
    dht.begin();
    connection.handle();
    healthCheck.handle();
    auth.handle();

    display.message("Ready!", 2000);
}

void App::loop(){
    unsigned long currentTime = millis();

    Serial.println(deviceState == ACTIVE ? "ACTIVE" : "SLEEP");
    
    if (currentTime >= (lastDataUpdate + power.getDataTransmittingDelay())){
        data = dataCollecting.handle(currentTime);

        if (deviceState == ACTIVE){
            vizualization.handle(data);
        }

        Serial.println("Data updated");
    }

    if (currentTime >= (lastDataTransmit + power.getDataTransmittingDelay())){
        if (network.shouldReconnect(currentTime)){
            connection.handle();
        }

        if (networkState == CONNECTED){
            server.handleClient();
            transmit.handle(data);
            lastDataTransmit = currentTime;
            Serial.println("Data transmitted");
        }
    }

    synchronization.handle(currentTime);
    toggleMode.handle(currentTime);
}
