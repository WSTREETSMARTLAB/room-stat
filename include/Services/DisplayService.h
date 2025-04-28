#pragma once
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class DisplayService
{
private:
    Adafruit_SSD1306 display;
public:
    DisplayService();
    bool begin();
    void clear();
    void turnOff();
    void turnOn();

    void message(const String message);
};
