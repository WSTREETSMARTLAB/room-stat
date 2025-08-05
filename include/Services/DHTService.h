#pragma once
#include <DHT.h>
#include <vector>
#include <Enum/Pin.h>

class DHTService
{
private:
    DHT dht;
public:
    DHTService();

    void begin();
    float* read();
};
