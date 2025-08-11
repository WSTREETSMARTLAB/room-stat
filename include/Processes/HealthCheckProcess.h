#pragma once
#include <Services/ApiService.h>
#include <Managers/DisplayManager.h>

class HealthCheckProcess
{
private:
    ApiService& apiService;
    DisplayManager& display;
public:
    HealthCheckProcess(ApiService& apiService, DisplayManager& display);
    void handle();
};
