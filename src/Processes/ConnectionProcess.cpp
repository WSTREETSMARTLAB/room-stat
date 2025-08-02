#include <Processes/ConnectionProcess.h>
#include <Storage/ToolPreferences.h>

ConnectionProcess::ConnectionProcess(NetworkService& network, ToolPreferences& preferences): 
network(network),
preferences(preferences){}

void ConnectionProcess::handle(){
    network.update();
    ToolConfig config = preferences.load();

    if (network.getCurrentState() == NetworkState::CONNECTED || network.getCurrentState() == NetworkState::AP_MODE){
        return;
    }

    if (config.wifi_ssid.length() > 0) {
        network.attemptConnection(config.wifi_ssid, config.wifi_pass);
    } else {
        network.startAP();
    }
}