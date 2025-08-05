#pragma once

class App
{
private:
    unsigned long lastDataUpdate = 0;
    unsigned long lastDataTransmit = 0;

    const unsigned long DATA_UPDATE_INTERVAL = 1000;
    const unsigned long DATA_TRANSMIT_INTERVAL = 5000;
public:
    void setup();
    void loop();
};








