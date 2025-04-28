#include <Processes/AuthProcess.h>
#include <ArduinoJson.h>
#include <Network/WiFiPointManager.h>


AuthProcess::AuthProcess(ApiService& apiServices, ToolConfig config)
    : apiService(apiService), config(config), endpoint("/core/api/v1/tools/auth")
{}

void AuthProcess::handle(){
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
            Serial.println("sensor is unauthorized");
            delay(2000);
            // show Auth Error message on display
            return;
        }
        
        String token = resDoc["token"] | "";

        if (token.length() > 0){
            apiService.setToken(token);
        }
    }
}