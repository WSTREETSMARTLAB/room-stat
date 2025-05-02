#pragma once
#include <WiFi.h>
#include <HTTPClient.h>

class ApiService
{
private:
    bool handleResponse(HTTPClient& http, int httpCode, String& response);
public:
    bool get(const String& endpoint, String& response);
    bool post(const String& endpoint, const String& payload, String& response);
};