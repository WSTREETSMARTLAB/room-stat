#pragma once
#include <Managers/DisplayManager.h>
#include <DTO/DataConfig.h>

class VizualizationDataProcess
{
private:
    DisplayManager& display;
public:
    VizualizationDataProcess(DisplayManager& display);
    void handle(DataConfig& data);
};