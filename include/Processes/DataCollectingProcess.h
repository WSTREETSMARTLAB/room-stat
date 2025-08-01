#pragma once
#include <Services/DHTService.h>
#include <Services/LDRService.h>
#include <DTO/DataConfig.h>

class DataCollectingProcess
{
private:
    DHTService& dht;
    LDRService& ldr;
public:
    DataCollectingProcess(DHTService& dht, LDRService& ldr);
    DataConfig handle();
};
