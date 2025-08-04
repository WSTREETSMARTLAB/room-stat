#include <Managers/AccessPointManager.h>
#include <Validators/ToolPreferencesValidator.h>
#include <Storage/ToolPreferences.h>
#include <Html/ToolConfigSetupHtml.h>
#include <Html/ValidationErrorHtml.h>
#include <Html/ValidationSuccessHtml.h>
#include <Html/RebootingHtml.h>
#include <Esp.h>

WebServer* AccessPointManager::_server = nullptr;

AccessPointManager::AccessPointManager(WebServer& server, DisplayService& display)
: display(display) 
{
    _server = &server;
}

void AccessPointManager::begin(String ssid, String password){
    WiFi.softAP(ssid, password);
    delay(500);
    IPAddress IP = WiFi.softAPIP();
    _server->on("/", HTTP_GET, handleRoot);
    _server->on("/submit", HTTP_POST, handleSubmit);
    _server->on("/reboot", HTTP_POST, handleReboot);
    _server->begin();
    display.message("Access Point Started", 3000);
    display.message("Please connect to Room-Stat-Setup, ...", 2000);
    display.message("...open 192.168.4.1 in browser...", 2000);
    display.message("...and set your Wi-Fi credentials", 2000);
};

void AccessPointManager::handleRoot(){
      _server->send(200, "text/html", toolConfigSetupHtmlForm);  
}

void AccessPointManager::handleSubmit(){
    ToolConfig config;
    ToolPreferencesValidator validator;
    ToolPreferences preferences;

    String code = _server->arg("code");
    String wifiSSID = _server->arg("wifi_ssid");
    String wifiPass = _server->arg("wifi_pass");

    if (!validator.validated(code, wifiSSID, wifiPass)){
      _server->send(422, "text/html", validationErrorHtml);
      return;
    }

    config.code = code;
    config.wifi_ssid = wifiSSID;
    config.wifi_pass = wifiPass;

    preferences.save(config);

    _server->send(200, "text/html", validationSuccessHtml);
}

void AccessPointManager::handleReboot() {
  _server->send(200, "text/html", rebootingHtml);
  delay(3000);

  WiFi.softAPdisconnect(true);
  delay(200);
  ESP.restart();
}