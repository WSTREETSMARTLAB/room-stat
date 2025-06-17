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

    bool success = wifiPointManager.connect(config.wifi_ssid, config.wifi_pass);

    if (!success) {
        accessPointManager.begin(ssid, pass);
        return;
    }
}