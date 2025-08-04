#include <Processes/AuthProcess.h>
#include <ArduinoJson.h>
#include <Managers/WiFiPointManager.h>
#include <DTO/ToolConfig.h>
#include <App/State.h>

AuthProcess::AuthProcess(ApiService& apiServices, ToolPreferences& preferences, DisplayService& display)
    : apiService(apiService), preferences(preferences), display(display)
{}

void AuthProcess::handle(){
    if (!WiFiPointManager::isConnected() || !serverAlive){
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

    display.message("Sending Auth Request", 2000);
    if(apiService.post("/core/api/v1/tools/auth", payload, response)){
        StaticJsonDocument<256> resDoc;
        DeserializationError error = deserializeJson(resDoc, response);

        if (error){
            display.message("Server Error", 2000);
            return;
        }
        
        token = resDoc["data"]["token"] | "";

        if (token != ""){
            display.message("Tool authorized", 2000);
            display.message("Now you can use a dashboard", 2000);
            display.message("www.wstreetsmartlab.systems", 2000);
        } else {
            display.message("Token not received", 2000);
            display.message("Please check a code", 2000);
        }
    }
}