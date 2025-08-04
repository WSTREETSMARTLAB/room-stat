#include <Services/ApiService.h>
#include <Managers/WiFiPointManager.h>
#include <App/State.h>

bool ApiService::get(const String& endpoint, String& response)
{
    if (!WiFiPointManager::isConnected()) {
        response = "Network Error";
        return false;
    }

    HTTPClient http;
    http.begin(serverUrl + endpoint);
    int httpCode = http.GET();

    return handleResponse(http, httpCode, response);
}

bool ApiService::post(const String& endpoint, const String& payload, String& response)
{
    if (!WiFiPointManager::isConnected()){
        response = "Network Error";
        return false;
    }

    HTTPClient http;
    http.begin(serverUrl + endpoint);
    http.addHeader("Content-Type", "application/json");
    
    if (token != "") {
        http.addHeader("Authorization", "Bearer " + token);
    }

    int httpCode = http.POST(payload);

    return handleResponse(http, httpCode, response);
}

bool ApiService::handleResponse(HTTPClient& http, int httpCode, String& response)
{
    if (httpCode > 0) {
        response = http.getString();
        http.end();
        return true;
    } else {
        response = "Request failed: " + http.errorToString(httpCode);
        http.end();
        return false;
    }
}