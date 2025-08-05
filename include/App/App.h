#pragma once

class App
{
private:
    unsigned long lastDataUpdate = 0;
    unsigned long lastDataTransmit = 0;
    
    const unsigned long DATA_UPDATE_INTERVAL = 1000;     // 1 секунда  
    const unsigned long DATA_TRANSMIT_INTERVAL = 5000;    // 5 секунд
public:
    void setup();
    void loop();
};








