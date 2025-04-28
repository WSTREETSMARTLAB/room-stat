#pragma once
#include <Services/ApiService.h>
#include <DTO/ToolConfig.h>

class AuthProcess
{
private:
    ApiService& apiService;
    ToolConfig config;
    const String endpoint;
public:
    AuthProcess(ApiService& apiService, const ToolConfig config);
    void handle();
};
