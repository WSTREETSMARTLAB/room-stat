#include <App/App.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Storage/ToolPreferences.h>
#include <Network/AccessPointManager.h>
#include <Network/WiFiPointManager.h>
#include <DTO/ToolConfig.h>
#include <DHT.h>
#include <Services/ApiService.h>
#include <Services/DisplayService.h>
#include <Processes/AuthProcess.h>
#include <Processes/ConnectionProcess.h>

#define DHT_PIN 4
#define DHT_TYPE DHT22

const char* serverUrl = "http://192.168.0.100:8080";

WebServer server(80);
AccessPointManager accessPointManager(server);
WiFiPointManager wifiPointManager;
ToolPreferences preferences;
ToolConfig config;
DHT dht(DHT_PIN, DHT_TYPE);
ApiService apiService(serverUrl);
DisplayService display;
AuthProcess auth(apiService, config, display);
ConnectionProcess connection(accessPointManager, wifiPointManager, display);

void App::setup(){
    display.begin();
    display.message("WSTREET LAB");
    delay(2000);

    bool wifiConnected = WiFiPointManager::isConnected();
    const String token;

    // dht.begin();

    if (!wifiConnected){
        connection.handle();
    }

    auth.handle();

    // show message - sensor is authorized on display
    display.message("Ready!");
    delay(2000);
}

void App::loop(){
    server.handleClient();

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Не удалось считать данные с DHT22");
        return;
    }

    Serial.println("===== Sensor Data: =====");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("===========================");
}