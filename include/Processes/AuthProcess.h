#pragma once
#include <Services/ApiService.h>
#include <DTO/ToolConfig.h>
#include <Services/DisplayService.h>
#include <Storage/ToolPreferences.h>

class AuthProcess
{
private:
    ApiService& apiService;
    ToolPreferences& preferences;
    ToolConfig config;
    DisplayService& display;
public:
    AuthProcess(ApiService& apiService, ToolPreferences& preferences, DisplayService& display);
    void handle();
};
