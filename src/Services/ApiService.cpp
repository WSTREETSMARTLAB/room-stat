#include <Services/ApiService.h>
#include <Network/WiFiPointManager.h>
#include <App/State.h>

ApiService::ApiService(const String& url): baseUrl(url)
{
}

bool ApiService::get(const String& endpoint, String& response)
{
    if (!WiFiPointManager::isConnected()) return "Network Error";

    HTTPClient http;
    http.begin(baseUrl + endpoint);
    int httpCode = http.GET();

    if (httpCode > 0){
        response = http.getString();
        http.end();
        return true;
    } else {
        response = "GET failed: " + http.errorToString(httpCode);
        http.end();
        return false;
    }
}

bool ApiService::post(const String& endpoint, const String& payload, String& response)
{
    if (!WiFiPointManager::isConnected()){
        response = "Network Error";
        return false;
    }

    HTTPClient http;
    http.begin(baseUrl + endpoint);
    http.addHeader("Content-Type", "application/json");
    
    if (token.length() > 0) {
        http.addHeader("Authorization", "Bearer " + token);
    }

    int httpCode = http.POST(payload);

    if (httpCode > 0) {
        response = http.getString();
        http.end();
        return true;
    } else {
        response = "POST failed: " + http.errorToString(httpCode);
        http.end();
        return false;
    }
}