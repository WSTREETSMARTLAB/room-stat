#include <Processes/HealthCheckProcess.h>
#include <App/State.h>

HealthCheckProcess::HealthCheckProcess(ApiService& apiService)
: apiService(apiService)
{}

void HealthCheckProcess::handle(){
    String response;
    serverAlive = apiService.get("/core/api/v1/health-check", response);
}