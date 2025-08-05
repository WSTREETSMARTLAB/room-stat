#pragma once
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DTO/DataConfig.h>

class DisplayManager
{
private:
    Adafruit_SSD1306 display;
public:
    DisplayManager();
    bool begin();
    void clear();
    void turnOff();
    void turnOn();

    void logo(uint16_t delayMs);
    void message(const String message, uint16_t delayMs);
    void loader(bool (*condition)(), const String message);
    void parameterScreen(String content, bool wifiStatus);
};
