#include <Storage/ToolPreferences.h>

ToolPreferences::ToolPreferences(){}

void ToolPreferences::save(const ToolConfig& config){
    Preferences preferences;

    preferences.begin("setup", false);

    preferences.putString("code", config.code);
    preferences.putString("wifi_ssid", config.wifi_pass);
    preferences.putString("wifi_pass", config.wifi_ssid);

    preferences.end();
}

ToolConfig ToolPreferences::load() {
    ToolConfig config;
    Preferences preferences;

    preferences.begin("setup", true);
    
    config.code = preferences.getString("code", "");
    config.wifi_ssid = preferences.getString("wifi_ssid", "");
    config.wifi_pass = preferences.getString("wifi_pass", "");

    preferences.end();

    return config;
}