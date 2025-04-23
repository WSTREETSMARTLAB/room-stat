#pragma once
#include <DTO/ToolConfig.h>
#include <Preferences.h>

class ToolPreferences
{
private:
public:
    ToolPreferences(/* args */);
    void save(const ToolConfig& config);
    ToolConfig load();
};
