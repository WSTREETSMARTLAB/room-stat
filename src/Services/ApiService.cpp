#include <Services/ApiService.h>
#include <Network/WiFiPointManager.h>

ApiService::ApiService(const String& url): baseUrl(url)
{
}

void ApiService::setToken(const String& token) {
    _token = token;
}

String ApiService::getToken() const {
    return _token;
}

String ApiService::get(const String& endpoint)
{
    if (!WiFiPointManager::isConnected()) return "Network Error";

    HTTPClient http;
    http.begin(baseUrl + endpoint);
    int httpCode = http.GET();

    String response;

    if (httpCode > 0){
        response = http.getString();
    }

    http.end();

    return response;
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
    
    if (_token.length() > 0) {
        http.addHeader("Authorization", "Bearer " + _token);
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