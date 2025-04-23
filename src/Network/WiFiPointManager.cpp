#include <Network/WiFiPointManager.h>
#include <WiFi.h>

bool WiFiPointManager::connect(const String ssid, const String password) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());

    Serial.print("Connecting to Wi-Fi");

    unsigned long startAttemptTime = millis();
    unsigned long timeout = 10000;

    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < timeout) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWi-Fi connected!"); // remove after test
        Serial.print("IP: "); // remove after test
        Serial.println(WiFi.localIP());
        return true;
    } else {
        Serial.println("\nFailed to connect to Wi-Fi."); // remove after test
        return false;
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