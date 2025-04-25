#include <Network/WiFiPointManager.h>
#include <WiFi.h>

void WiFiPointManager::connect(const String ssid, const String password) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());

    Serial.print("Connecting to Wi-Fi");

    unsigned long startAttemptTime = millis();
    unsigned long timeout = 10000;

    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < timeout) {
        delay(500);
        Serial.print(".");
    }
}

bool WiFiPointManager::isConnected() const {
    return WiFi.status() == WL_CONNECTED;
}

IPAddress WiFiPointManager::getIP() const {
    if (WiFi.status() == WL_CONNECTED) {
        return WiFi.localIP();
    }
    return IPAddress(0, 0, 0, 0);
}