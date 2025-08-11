#include <Processes/AuthProcess.h>
#include <ArduinoJson.h>
#include <Managers/WiFiPointManager.h>
#include <DTO/ToolConfig.h>
#include <App/State.h>

AuthProcess::AuthProcess(ApiService& apiServices, ToolPreferences& preferences, DisplayManager& display)
    : apiService(apiService), preferences(preferences), display(display)
{}

void AuthProcess::handle(){
    if (!WiFiPointManager::isConnected() || !serverAlive){
        return;
    }

    ToolConfig config;
    config = preferences.load();

    StaticJsonDocument<256> doc;
    doc["type"] = config.type;
    doc["code"] = config.code;
    
    String payload;
    serializeJson(doc, payload);

    String response;

    if(apiService.post("/core/api/v1/tools/auth", payload, response)){
        StaticJsonDocument<256> resDoc;
        DeserializationError error = deserializeJson(resDoc, response);

        if (error){
            display.message("Server Error", 2000);
            return;
        }
        
        token = resDoc["data"]["token"] | "";

        if (token != ""){
            display.message("Tool authorized", 1000);
        } else {
            display.message("Error. Please check a code", 2000);
        }
    }
}