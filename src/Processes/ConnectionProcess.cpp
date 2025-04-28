#include <Processes/ConnectionProcess.h>
#include <Storage/ToolPreferences.h>

ConnectionProcess::ConnectionProcess(AccessPointManager& accessPointManager, WiFiPointManager& wifiPointManager)
    : ssid("Room_Stat_Access"), pass("password"), accessPointManager(accessPointManager), wifiPointManager(wifiPointManager)
{
    ToolPreferences preferences;
    config = preferences.load();
}

void ConnectionProcess::handle(){
    if(config.code == ""){
        accessPointManager.begin(ssid, pass);
    } else {
        wifiPointManager.connect(config.wifi_ssid, config.wifi_pass);
    }
}