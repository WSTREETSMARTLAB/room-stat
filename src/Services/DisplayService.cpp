#include <Services/DisplayService.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

DisplayService::DisplayService()
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, SCREEN_ADDRESS)
{}