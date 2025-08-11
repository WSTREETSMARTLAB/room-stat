#pragma once
#include <Services/ApiService.h>
#include <DTO/ToolConfig.h>
#include <Managers/DisplayManager.h>
#include <Storage/ToolPreferences.h>

class AuthProcess
{
private:
    ApiService& apiService;
    ToolPreferences& preferences;
    ToolConfig config;
    DisplayManager& display;
public:
    AuthProcess(ApiService& apiService, ToolPreferences& preferences, DisplayManager& display);
    void handle();
};
