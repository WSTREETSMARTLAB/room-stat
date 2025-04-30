#pragma once
#include <Services/ApiService.h>

class HealthCheckProcess
{
private:
    bool _serverAlive;
    ApiService& apiService;
public:
    HealthCheckProcess(ApiService& apiService);
    void handle();
};
