#pragma once
#include <Services/DHTService.h>
#include <Services/LDRService.h>
#include <DTO/DataConfig.h>
#include <Managers/PowerManager.h>

class DataCollectingProcess
{
private:
    DHTService& dht;
    LDRService& ldr;
    PowerManager& power;
public:
    DataCollectingProcess(DHTService& dht, LDRService& ldr, PowerManager& power);
    DataConfig handle(unsigned long currentTime);
};
