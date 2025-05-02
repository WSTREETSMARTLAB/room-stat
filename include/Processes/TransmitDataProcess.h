#pragma once
#include <Services/ApiService.h>
#include <DTO/DataConfig.h>

class TransmitDataProcess
{
private:
    ApiService& api;
public:
    TransmitDataProcess(ApiService& api);
    void handle(DataConfig& data);
};