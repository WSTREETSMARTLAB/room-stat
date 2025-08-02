#include <Processes/ConnectionProcess.h>
#include <Storage/ToolPreferences.h>

ConnectionProcess::ConnectionProcess(NetworkService& network, ToolPreferences& preferences): 
network(network), 
preferences(preferences), 
initialConnectionAttempted(false), 
lastConfigCheck(0)
{
}

void ConnectionProcess::handle(){
    network.update();

    if (millis() - lastConfigCheck >= 30000) {
        ToolConfig config = preferences.load();
        lastConfigCheck = millis();
        
        // Если есть сохраненные данные Wi-Fi и мы не подключены, пытаемся подключиться
        if (config.wifi_ssid.length() > 0 && network.getCurrentState() == NetworkState::DISCONNECTED) {
            attemptInitialConnection();
        }
    }
    // bool success = wifiPointManager.connect(config.wifi_ssid, config.wifi_pass);

    // if (!success) {
    //     accessPointManager.begin(ssid, pass);
    //     return;
    // }
}