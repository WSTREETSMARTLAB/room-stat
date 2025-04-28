#include <Processes/ConnectionProcess.h>
#include <Storage/ToolPreferences.h>

ConnectionProcess::ConnectionProcess(AccessPointManager& accessPointManager, WiFiPointManager& wifiPointManager, DisplayService& display): 
ssid("Room_Stat_Access"), 
pass("password"), 
accessPointManager(accessPointManager), 
wifiPointManager(wifiPointManager),
display(display)
{
    ToolPreferences preferences;
    config = preferences.load();
}

void ConnectionProcess::handle(){
    if(config.code == ""){
        accessPointManager.begin(ssid, pass);
        display.message("Access Point Created", 3000);
    } else {
        display.message("Connecting to Wi-Fi...", 1000);
        wifiPointManager.connect(config.wifi_ssid, config.wifi_pass);
        display.loader(WiFiPointManager::isConnected, "Connecting Wi-Fi");
        display.message("Wi-Fi Connected", 3000);
    }
}