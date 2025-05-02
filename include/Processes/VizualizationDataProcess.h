#pragma once
#include <Services/DisplayService.h>
#include <DTO/DataConfig.h>

class VizualizationDataProcess
{
private:
    DisplayService& display;
public:
    VizualizationDataProcess(DisplayService& display);
    void handle(DataConfig& data);
};