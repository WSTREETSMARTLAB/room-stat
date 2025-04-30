#pragma once
#include <WiFi.h>
#include <HTTPClient.h>

class ApiService
{
private:
    const String baseUrl;
    bool handleResponse(HTTPClient& http, int httpCode, String& response);
public:
    ApiService(const String& url);

    bool get(const String& endpoint, String& response);
    bool post(const String& endpoint, const String& payload, String& response);
};