#include <Storage/ToolPrefernces.h>


ToolPrefernces::ToolPrefernces(){}

void save(const ToolConfig& config){
    Preferences preferences;

    preferences.begin("setup", true);

    preferences.begin("setup", false);
    preferences.putString("tool_name", config.code);
    preferences.putString("wifi_ssid", config.wifi_pass);
    preferences.putString("wifi_pass", config.wifi_ssid);

    preferences.end();
}

ToolConfig load() {
    ToolConfig config;

}