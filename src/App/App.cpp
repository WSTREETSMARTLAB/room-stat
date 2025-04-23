#include <App/App.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Storage/ToolPreferences.h>
#include <Network/AccessPointManager.h>
#include <DTO/ToolConfig.h>

const char* ssid = "Room-Stat-Setup";
const char* password = "11112222";

void handleRoot();
void handleSubmit();

WebServer server(80);
AccessPointManager accessPointManager(server);
ToolPreferences preferences;
ToolConfig config;

App::App() {
    
}

void App::setup(){
    config = preferences.load();

    if(config.code == ""){
        accessPointManager.begin(ssid, password);
    }

    // start wi-fi server with config.wifi_ssid , config.wifi_pass
}

void App::loop(){
    server.handleClient();

    config = preferences.load();

    Serial.println("===== ДАННЫЕ ИЗ FLASH =====");
    Serial.println("Type: " + config.type);
    Serial.println("Code: " + config.code);
    Serial.println("Wi-Fi SSID: " + config.wifi_ssid);
    Serial.println("Wi-Fi пароль: " + config.wifi_pass);
    Serial.println("===========================");
}