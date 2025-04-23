#pragma once
#include <Arduino.h>

class ToolPreferencesValidator
{
private:
public:
    static bool isValidCode(const String& code);
    static bool isValidSSID(const String& ssid);
    static bool isValidPass(const String& pass);

    static bool validated(const String& code, const String& ssid, const String& pass);
};