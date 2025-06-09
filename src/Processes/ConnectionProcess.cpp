#include <Processes/ConnectionProcess.h>
#include <Storage/ToolPreferences.h>

ConnectionProcess::ConnectionProcess(AccessPointManager& accessPointManager, WiFiPointManager& wifiPointManager, ToolPreferences& preferences): 
ssid("Room_Stat_Access"), 
pass(""), 
accessPointManager(accessPointManager), 
wifiPointManager(wifiPointManager),
preferences(preferences)
{
}

void ConnectionProcess::handle(){
    ToolConfig config;
    config = preferences.load();

    if(config.code == ""){
        accessPointManager.begin(ssid, pass);
    } else {
        wifiPointManager.connect(config.wifi_ssid, config.wifi_pass);
    }

    
}