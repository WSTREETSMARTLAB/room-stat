#include <Network/WiFiPointManager.h>
#include <WiFi.h>

WiFiPointManager::WiFiPointManager(DisplayService& display)
: display(display)
{}

bool WiFiPointManager::connect(const String ssid, const String password) {
    const int attempts = 3;
    WiFi.mode(WIFI_STA);

    for (int i = 0; i < attempts; i++){
        WiFi.begin(ssid.c_str(), password.c_str());
        String message = "Connecting to " + ssid;
        display.loader(WiFiPointManager::isConnected, message);

        const unsigned long timeout = 10000;
        unsigned long startTime = millis();
        while (WiFi.status() != WL_CONNECTED && millis() - startTime < timeout) {
            delay(100);
        }

        if (isConnected()){
            return true;
        }

        WiFi.disconnect();
        delay(1000);
    }
        
    return false;
}

bool WiFiPointManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

IPAddress WiFiPointManager::getIP() const {
    if (WiFi.status() == WL_CONNECTED) {
        return WiFi.localIP();
    }
    return IPAddress(0, 0, 0, 0);
}