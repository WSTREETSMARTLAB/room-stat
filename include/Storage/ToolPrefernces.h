#pragma once
#include <DTO/ToolConfig.h>
#include <Preferences.h>

class ToolPrefernces
{
private:
    ToolConfig load();
public:
    ToolPrefernces(/* args */);
    void save(const ToolConfig& config);
};
