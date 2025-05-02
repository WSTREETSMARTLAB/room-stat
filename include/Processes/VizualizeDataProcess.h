#pragma once
#include <Services/DisplayService.h>
#include <DTO/DataConfig.h>

class VizualizeDataProcess
{
private:
    DisplayService& display;
public:
    VizualizeDataProcess(DisplayService& display);
    void handle(DataConfig data);
};