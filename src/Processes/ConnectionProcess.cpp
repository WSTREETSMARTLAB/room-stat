#include <Processes/ConnectionProcess.h>
#include <Storage/ToolPreferences.h>

ConnectionProcess::ConnectionProcess(NetworkService& network, DisplayManager& display, ToolPreferences& preferences): 
network(network),
preferences(preferences),
display(display)
{}

void ConnectionProcess::handle(){
    ToolConfig config = preferences.load();

    if (network.getCurrentState() == NetworkState::CONNECTED || network.getCurrentState() == NetworkState::AP_MODE){
        return;
    }

    if (config.wifi_ssid.length() > 0) {
        display.message("Connecting to Wi-Fi", 1000);
        network.attemptConnection(config.wifi_ssid, config.wifi_pass);

        if (network.getCurrentState() == CONNECTED){
            display.message("Connected", 1000);
        } else {
            display.message("Connection failed", 1000);
            network.update(millis());
        }
    } else {
        network.startAP();
        display.message("Access Point Started", 2000);
    }
}