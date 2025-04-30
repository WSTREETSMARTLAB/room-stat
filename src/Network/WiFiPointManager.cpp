#include <Network/WiFiPointManager.h>
#include <WiFi.h>

WiFiPointManager::WiFiPointManager(DisplayService& display)
: display(display)
{}

void WiFiPointManager::connect(const String ssid, const String password) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    unsigned long startAttemptTime = millis();
    unsigned long timeout = 10000;
    String message = "Connecting to " + ssid;
    display.loader(WiFiPointManager::isConnected, message);
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