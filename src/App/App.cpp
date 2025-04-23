#include <App/App.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <Network/AccessPointManager.h>

const char* ssid = "Room-Stat-Setup";
const char* password = "11112222";

void handleRoot();
void handleSubmit();

bool wasRead = false;

WebServer server(80);
Preferences preferences;
AccessPointManager accessPointManager(server);

App::App() {
    
}

void App::setup(){
    preferences.begin("setup", true); 
    String code = preferences.getString("code", "");
    preferences.end();

    if(code == ""){
        accessPointManager.begin(ssid, password);
    }
}

void App::loop(){
    server.handleClient();

    if(!wasRead){
        preferences.begin("setup", true);

        String code     = preferences.getString("code", "");
        String wifiPASS = preferences.getString("wifi_pass", "n/a");
        String wifiSSID = preferences.getString("wifi_ssid", "n/a");

        wasRead = true;
        preferences.end();

        Serial.println("===== ДАННЫЕ ИЗ FLASH =====");
        Serial.println("Code: " + code);
        Serial.println("Wi-Fi SSID: " + wifiSSID);
        Serial.println("Wi-Fi пароль: " + wifiPASS);
        Serial.println("===========================");
  }

  wasRead = false;
}