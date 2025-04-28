#include <Processes/AuthProcess.h>
#include <ArduinoJson.h>
#include <Network/WiFiPointManager.h>


AuthProcess::AuthProcess(ApiService& apiServices, ToolConfig config, DisplayService& display)
    : apiService(apiService), config(config), endpoint("/core/api/v1/tools/auth"), display(display)
{}

void AuthProcess::handle(){
    if (!WiFiPointManager::isConnected){
        return;
    }

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
        
        String token = resDoc["token"] | "";

        if (token.length() > 0){
            apiService.setToken(token);
            display.message("Auth Success", 2000);
        }
    }
}