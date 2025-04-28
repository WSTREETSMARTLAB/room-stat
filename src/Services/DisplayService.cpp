#include <Services/DisplayService.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

DisplayService::DisplayService()
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, SCREEN_ADDRESS)
{}

bool DisplayService::begin(){
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        return false;
    }

    display.clearDisplay();
    display.display();

    return true;
}

void DisplayService::clear(){
    display.clearDisplay();
    display.display();
}

void DisplayService::turnOn(){
    display.ssd1306_command(SSD1306_DISPLAYON);
}

void DisplayService::turnOff(){
    display.ssd1306_command(SSD1306_DISPLAYOFF);
}

void DisplayService::message(const String message){
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(message);
    display.display();
}