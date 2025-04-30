#include <Processes/AuthProcess.h>
#include <ArduinoJson.h>
#include <Network/WiFiPointManager.h>
#include <DTO/ToolConfig.h>
#include <App/State.h>

AuthProcess::AuthProcess(ApiService& apiServices, ToolPreferences& preferences, DisplayService& display)
    : apiService(apiService), endpoint("/core/api/v1/tools/auth"), preferences(preferences), display(display)
{}

void AuthProcess::handle(){
    if (!WiFiPointManager::isConnected || !serverAlive){
        return;
    }

    ToolConfig config;
    config = preferences.load();

    display.message("Auth Tool", 3000);
    StaticJsonDocument<256> doc;
    doc["type"] = config.type;
    doc["code"] = config.code;
    
    String payload;
    serializeJson(doc, payload);

    String response;

    if(apiService.post(endpoint, payload, response)){
        StaticJsonDocument<256> resDoc;
        DeserializationError error = deserializeJson(resDoc, response);

        if (error){
            display.message("Auth Error", 2000);
            return;
        }
        
        token = resDoc["token"] | "";

        if (token.length() > 0){
            display.message("Auth Success", 2000);
        } else {
            display.message("Auth Error", 2000);
        }
    }
}