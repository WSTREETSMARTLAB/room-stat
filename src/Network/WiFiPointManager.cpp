#include <Network/WiFiPointManager.h>
#include <WiFi.h>

WiFiPointManager::WiFiPointManager(DisplayService& display)
: display(display)
{}

void WiFiPointManager::connect(const String ssid, const String password) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    String message = "Connecting to " + ssid;
    display.loader([]() { return isConnected(); }, message);

    if (!isConnected()){
        WiFi.disconnect();
        delay(1000);
    }
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