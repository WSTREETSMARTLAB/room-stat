#include <Validators/ToolPreferencesValidator.h>

bool ToolPreferencesValidator::isValidCode(const String& code){
    return code.length() == 9;
}

bool ToolPreferencesValidator::isValidPass(const String& pass){
    return pass.length() >= 3 && pass.length() <=32;
}

bool ToolPreferencesValidator::isValidSSID(const String& ssid){
    return ssid.length() >= 3 && ssid.length() <=32;
}

bool ToolPreferencesValidator::validated(const String& code, const String& ssid, const String& pass){
    return isValidCode(code) && isValidSSID(ssid) && isValidPass(pass);
}
