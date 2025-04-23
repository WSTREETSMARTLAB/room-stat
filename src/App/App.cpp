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

bool wasRead = false;

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
}

void App::loop(){
    server.handleClient();

    if(!wasRead){
        config = preferences.load();

        Serial.println("===== ДАННЫЕ ИЗ FLASH =====");
        Serial.println("Code: " + config.code);
        Serial.println("Wi-Fi SSID: " + config.code);
        Serial.println("Wi-Fi пароль: " + config.code);
        Serial.println("===========================");
  }

  wasRead = false;
}