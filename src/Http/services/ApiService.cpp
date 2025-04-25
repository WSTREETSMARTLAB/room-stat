#include <Http/services/ApiService.h>

ApiService::ApiService(const String& url): baseUrl(url)
{
}

String ApiService::get(const String& endpoint)
{
    return "";
}

bool ApiService::post(const String& endpoint, const String& payload, String& response)
{
    return false;
}
