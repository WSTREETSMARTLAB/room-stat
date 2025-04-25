#pragma once
#include <WiFi.h>
#include <HTTPClient.h>

class ApiService
{
private:
    const String baseUrl;
    String _token;
public:
    ApiService(const String& url);
    void setToken(const String& token);
    String getToken() const;

    String get(const String& endpoint);
    bool post(const String& endpoint, const String& payload, String& response);
};