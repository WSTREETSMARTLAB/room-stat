#include <Processes/TransmitDataProcess.h>
#include <Managers/WiFiPointManager.h>
#include <App/State.h>
#include <ArduinoJson.h>

TransmitDataProcess::TransmitDataProcess(ApiService& api)
: api(api)
{}

void TransmitDataProcess::handle(DataConfig& data){
    if (!WiFiPointManager::isConnected() || !serverAlive){
        return;
    }

    StaticJsonDocument<256> doc;
    String payload;
    String response;
    doc["temperature"] = data.temperature;
    doc["humidity"] = data.humidity;
    doc["light"] = data.light;
    serializeJson(doc, payload);
    api.post("/room-stat/api/v1/transmit", payload, response);
}