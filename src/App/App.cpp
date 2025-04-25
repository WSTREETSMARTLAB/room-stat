#include <App/App.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Storage/ToolPreferences.h>
#include <Network/AccessPointManager.h>
#include <Network/WiFiPointManager.h>
#include <DTO/ToolConfig.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Http/services/ApiService.h>

#define DHT_PIN 4
#define DHT_TYPE DHT22

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

const char* ssid = "Room-Stat-Setup";
const char* password = "11112222";
const char* serverUrl = "http://192.168.0.100:8080";

WebServer server(80);
AccessPointManager accessPointManager(server);
WiFiPointManager wifiPointManager;
ToolPreferences preferences;
ToolConfig config;
DHT dht(DHT_PIN, DHT_TYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, SCREEN_ADDRESS);
ApiService apiService(serverUrl);

App::App() {
    
}

void App::setup(){
    bool wifiConnected = wifiPointManager.isConnected();
    config = preferences.load();
    const String token;

    if (!wifiConnected){
        if(config.code == ""){
            accessPointManager.begin(ssid, password);
        } else {
            wifiPointManager.connect(config.wifi_ssid, config.wifi_pass);
        }
    }

    // format json
    String json = "{\"temperature\": 25.6}";
    String response;

    apiService.post("/core/api/v1/tools/auth", json, response);
    apiService.setToken(""); // set token from response

    // if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
    //     Serial.println(F("Не удалось инициализировать OLED дисплей"));
    //     while (true);
    // }
    
    // display.clearDisplay();
    // display.setTextSize(1);
    // display.setTextColor(SSD1306_WHITE);
    // display.setCursor(0, 0);
    // display.println("WSTREET SMART LAB");
    // display.display();

    // dht.begin();
}

void App::loop(){
    server.handleClient();

    Serial.println("===== Wi Fi Connected. Device Data: =====");
    Serial.println("Type: " + config.type);
    Serial.println("Code: " + config.code);
    Serial.println("Wi-Fi SSID: " + config.wifi_ssid);
    Serial.println("Wi-Fi пароль: " + config.wifi_pass);
    Serial.println("===========================");

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Не удалось считать данные с DHT22");
        return;
    }

    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.print(temperature, 1);
    display.println(" C, ");
    display.print(humidity, 1);
    display.println(" %");
    display.display();

    Serial.println("===== Sensor Data: =====");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("===========================");
}