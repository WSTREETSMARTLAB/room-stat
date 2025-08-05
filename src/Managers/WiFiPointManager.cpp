#include <Managers/WiFiPointManager.h>
#include <WiFi.h>

WiFiPointManager::WiFiPointManager()
{}

void WiFiPointManager::connect(const String ssid, const String password) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    delay(2000);
}

void WiFiPointManager::disconnect(){
    WiFi.disconnect();
    delay(2000);
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