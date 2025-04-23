#include <Network/AccessPointManager.h>
#include <Validators/ToolPreferencesValidator.h>
#include <Storage/ToolPreferences.h>

WebServer* AccessPointManager::_server = nullptr;

AccessPointManager::AccessPointManager(WebServer& server) {
    _server = &server;
}

void AccessPointManager::begin(String ssid, String password){
    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
    _server->on("/", HTTP_GET, handleRoot);
    _server->on("/submit", HTTP_POST, handleSubmit);
    _server->begin();
};

void AccessPointManager::handleRoot(){
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
            <label>Code:</label>
            <input type="text" name="code" required>
            <label>Wi-Fi SSID:</label>
            <input type="text" name="wifi_ssid" required>
            <label>Wi-Fi Password:</label>
            <input type="password" name="wifi_pass" required>
            <input type="submit" value="Register">
          </form>
        </body>
        </html>
      )rawliteral";

      _server->send(200, "text/html", html);  
}

void AccessPointManager::handleSubmit(){
    ToolConfig config;
    ToolPreferencesValidator validator;
    ToolPreferences preferences;

    String code = _server->arg("code");
    String wifiSSID = _server->arg("wifi_ssid");
    String wifiPass = _server->arg("wifi_pass");

    if (!validator.validated(code, wifiSSID, wifiPass)){
        String html = R"rawliteral(
            <html>
            <head><title>Validation Error</title></head>
            <body>
              <h2>Validation Error</h2>
              <button onclick="window.history.back()">Back</button>
            </body>
            </html>
        )rawliteral";

      _server->send(422, "text/html", html);
      return;
    }

    config.code = code;
    config.wifi_ssid = wifiSSID;
    config.wifi_pass = wifiPass;

    preferences.save(config);
  
    // send success page with btn to reboot device (with next reboot data will not open the server)
    _server->send(200, "text/html", "data received");
}