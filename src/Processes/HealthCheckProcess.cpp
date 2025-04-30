#include <Processes/HealthCheckProcess.h>

HealthCheckProcess::HealthCheckProcess(ApiService& apiService): apiService(apiService){}

void HealthCheckProcess::handle(){
    _serverAlive = false;

    
    apiService.get("/core/api/v1/health-check");
}