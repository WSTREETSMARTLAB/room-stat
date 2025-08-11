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
DataCollectingProcess dataCollecting(dht, ldr);
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
    DeviceState state = deviceState;

    Serial.println("loop: " + String(currentTime));

    synchronization.handle(currentTime);

    if (state != deviceState){
        toggleMode.handle(state);
    }

    if (!lastDataUpdate){
        lastDataUpdate = currentTime - power.getInterval();
    }
    
    if (currentTime - lastDataUpdate >= power.getInterval()){
        data = dataCollecting.handle();

        if (network.shouldReconnect(currentTime)){
            connection.handle();
        }

        if (networkState == CONNECTED){
            server.handleClient();
            transmit.handle(data);
        }
        
        lastDataUpdate = currentTime;
    }

    if (deviceState == ACTIVE){
        vizualization.handle(data);
    }
}
