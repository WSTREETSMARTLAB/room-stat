#include <Network/AccessPointManager.h>
#include <Validators/ToolPreferencesValidator.h>
#include <Storage/ToolPreferences.h>
#include <Http/view/ToolConfigSetupHtml.h>
#include <Http/view/ValidationErrorHtml.h>

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
  
    // send success page with btn to reboot device (with next reboot data will not open the server)

    

    _server->send(200, "text/html", "data received");
}