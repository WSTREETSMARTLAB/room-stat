#pragma once
#include <DHT.h>
#include <vector>

class DHTService
{
private:
    DHT dht;
public:
    DHTService();

    void begin();
    float* read();
};
