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
    ToolConfig config = preferences.load();

    if (config.wifi_ssid.length() > 0) {
        network.attemptConnection(config.wifi_ssid, config.wifi_pass);
    } else {
        network.startAP();
    }
}