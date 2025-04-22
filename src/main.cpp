#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Room-Stat-Setup";
const char* password = "11112222";

WebServer server(80);

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

  server.send(200, "text/html","data received");
}

void setup() {
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

  // create wi-fi access point
  // save tool auth and wi-fi credentials
  // 
  // connect to wi-fi with saved credentials
  // check server status
  //
  // if status = ok - login user
  // use token to auth requests
}

void loop() {
  server.handleClient();
  // get sensor params
  // format json
  // send request to transmit api
}