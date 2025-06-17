#include <Services/DisplayService.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

DisplayService::DisplayService()
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
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

void DisplayService::logo(uint16_t delayMs){
    const unsigned char cloudBitmap [] PROGMEM = {
        0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x3C,0x00,0x00,0x00,
        0x00,0x01,0xFF,0xC0,0x00,0x00,
        0x00,0x07,0xFF,0xF0,0x00,0x00,
        0x00,0x1F,0xFF,0xF8,0x00,0x00,
        0x00,0x3F,0xFF,0xFC,0x00,0x00,
        0x00,0x7F,0xC1,0xFE,0x00,0x00,
        0x00,0xFF,0x00,0xFF,0x00,0x00,
        0x01,0xFE,0x00,0x7F,0x80,0x00,
        0x03,0xFC,0x00,0x3F,0xC0,0x00,
        0x03,0xF8,0x00,0x1F,0xC0,0x00,
        0x07,0xF0,0x00,0x0F,0xE0,0x00,
        0x07,0xE0,0x00,0x07,0xE0,0x00,
        0x07,0xE0,0x00,0x07,0xE0,0x00,
        0x07,0xE0,0x00,0x07,0xE0,0x00,
        0x07,0xF0,0x00,0x0F,0xE0,0x00,
        0x03,0xF8,0x00,0x1F,0xC0,0x00,
        0x03,0xFC,0x00,0x3F,0xC0,0x00,
        0x01,0xFE,0x00,0x7F,0x80,0x00,
        0x00,0xFF,0x00,0xFF,0x00,0x00,
        0x00,0x7F,0xC1,0xFE,0x00,0x00,
        0x00,0x3F,0xFF,0xFC,0x00,0x00,
        0x00,0x1F,0xFF,0xF8,0x00,0x00,
        0x00,0x07,0xFF,0xF0,0x00,0x00,
        0x00,0x01,0xFF,0xC0,0x00,0x00,
        0x00,0x00,0x3C,0x00,0x00,0x00,
      };


    display.clearDisplay();
    display.drawBitmap(
        (SCREEN_WIDTH - 48) / 2,
        (SCREEN_HEIGHT - 24) / 2,
        cloudBitmap,
        48, 24,
        SSD1306_WHITE
      );
    
    display.display();
    delay(2000);
}

void DisplayService::message(const String message, uint16_t delayMs){
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print(message);
    display.display();
    delay(delayMs);
}

void DisplayService::loader(bool (*condition)(), const String message){
    uint8_t dotCount = 0;
    while (!condition()){
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.print(message);

        for (uint8_t i = 0; i < dotCount; i++){
            display.print(".");
        }

        display.display();
        delay(500);
        
        dotCount = (dotCount + 1) % 4;
    }
}

void DisplayService::parameterScreen(String content, bool wifiStatus)
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);

    display.setCursor(0, 0);
    display.print("Room v1");

    display.setCursor(80, 0);
    display.print(wifiStatus ? "[WiFi:+]" : "[WiFi:-]"); // set icons

    display.setCursor(0, 12);
    display.print(content);

    display.display();
}