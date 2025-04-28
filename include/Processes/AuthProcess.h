#pragma once
#include <Services/ApiService.h>
#include <DTO/ToolConfig.h>
#include <Services/DisplayService.h>

class AuthProcess
{
private:
    ApiService& apiService;
    ToolConfig config;
    DisplayService& display;
    const String endpoint;
public:
    AuthProcess(ApiService& apiService, const ToolConfig config, DisplayService& display);
    void handle();
};
