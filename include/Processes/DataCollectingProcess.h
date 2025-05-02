#pragma once
#include <Services/DHTService.h>
#include <DTO/DataConfig.h>

class DataCollectingProcess
{
private:
    DHTService& dht;
public:
    DataCollectingProcess(DHTService& dht);
    DataConfig handle();
};
