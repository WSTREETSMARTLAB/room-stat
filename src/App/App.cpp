#include <App/App.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>

const char* ssid = "Room-Stat-Setup";
const char* password = "11112222";

void handleRoot();
void handleSubmit();

bool wasRead = false;

WebServer server(80);
Preferences preferences;

App::App() {
    
}

void App::setup(){
    Serial.begin(115200);
    delay(2000);
  
    Serial.print("access point start");
    WiFi.softAP(ssid, password);
  
    IPAddress IP = WiFi.softAPIP();
  
    Serial.print("access point created");
    Serial.println(IP);
  
    server.on("/", HTTP_GET, handleRoot);
    server.on("/submit", HTTP_POST, handleSubmit);
  
    server.begin();
    Serial.println("Server started");
}

void App::loop(){
    server.handleClient();

    if(!wasRead){
        preferences.begin("setup", true);

        String password = preferences.getString("tool_pass", "n/a");
        String name     = preferences.getString("tool_name", "n/a");
        String wifiPASS = preferences.getString("wifi_pass", "n/a");
        String wifiSSID = preferences.getString("wifi_ssid", "n/a");

        wasRead = true;
        preferences.end();

        Serial.println("===== ДАННЫЕ ИЗ FLASH =====");
        Serial.println("Имя устройства: " + name);
        Serial.println("Пароль: " + password);
        Serial.println("Wi-Fi SSID: " + wifiSSID);
        Serial.println("Wi-Fi пароль: " + wifiPASS);
        Serial.println("===========================");
  }

  wasRead = false;
}

void handleRoot() {
    String html = R"rawliteral(
      <!DOCTYPE html>
      <html>
      <head>
        <title>Device Setup</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <style>
          body { font-family: Arial; padding: 20px; background: #f4f4f4; }
          form { background: white; padding: 20px; border-radius: 8px; max-width: 300px; margin: auto; }
          input[type="text"], input[type="password"] {
            width: 100%; padding: 8px; margin: 6px 0; border: 1px solid #ccc; border-radius: 4px;
          }
          input[type="submit"] {
            background-color: #4CAF50; color: white; padding: 10px;
            border: none; border-radius: 4px; cursor: pointer;
          }
        </style>
      </head>
      <body>
        <h2>Register Device</h2>
        <form action="/submit" method="POST">
          <label>Device Name:</label>
          <input type="text" name="name" required>
          <label>Device Password:</label>
          <input type="password" name="password" required>
          <label>Wi-Fi SSID:</label>
          <input type="text" name="wifi_ssid" required>
          <label>Wi-Fi Password:</label>
          <input type="password" name="wifi_pass" required>
          <input type="submit" value="Register">
        </form>
      </body>
      </html>
    )rawliteral";
  
    server.send(200, "text/html", html);
  }

  void handleSubmit () {
    String name = server.arg("name");
    String password = server.arg("password");
    String wifiSSID = server.arg("wifi_ssid");
    String wifiPASS = server.arg("wifi_pass");
  
    preferences.begin("setup", false);
    preferences.putString("tool_name", name);
    preferences.putString("tool_pass", password);
    preferences.putString("wifi_ssid", wifiSSID);
    preferences.putString("wifi_pass", wifiPASS);
  
    server.send(200, "text/html","data received");
  }