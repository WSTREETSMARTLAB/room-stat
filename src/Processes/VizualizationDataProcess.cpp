#include <Processes/VizualizationDataProcess.h>
#include <Network/WiFiPointManager.h>

VizualizationDataProcess::VizualizationDataProcess(DisplayService& display)
: display(display) 
{}

void VizualizationDataProcess::handle(DataConfig& data)
{
    String content;
    String temp = "T: " + String(data.temperature, 1) + "C";
    String hum  = "H: " + String(data.humidity, 0) + "%";
    String light = "L: " + String(data.light) + "%";
    content = temp + "\n" + hum + "\n" + light;

    display.parameterScreen(content, WiFiPointManager::isConnected());
}