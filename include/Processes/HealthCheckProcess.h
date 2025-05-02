#pragma once
#include <Services/ApiService.h>
#include <Services/DisplayService.h>

class HealthCheckProcess
{
private:
    ApiService& apiService;
    DisplayService& display;
public:
    HealthCheckProcess(ApiService& apiService, DisplayService& display);
    void handle();
};
