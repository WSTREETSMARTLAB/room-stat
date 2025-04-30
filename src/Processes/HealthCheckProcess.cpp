#include <Processes/HealthCheckProcess.h>
#include <App/State.h>

HealthCheckProcess::HealthCheckProcess(ApiService& apiService, DisplayService& display)
: apiService(apiService), display(display)
{}

void HealthCheckProcess::handle(){
    String response;
    serverAlive = apiService.get("/core/api/v1/health-check", response);

    if (serverAlive){
        display.message("Server is ready", 2000);
    } else {
        display.message("Server Error", 2000);
    }
}