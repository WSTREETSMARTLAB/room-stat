#pragma once
#include <WiFi.h>
#include <HTTPClient.h>

class ApiService
{
private:
    const String baseUrl;
public:
    ApiService(const String& url);
    String get(const String& endpoint);
    bool post(const String& endpoint, const String& payload, String& response);
};