#include <Services/DHTService.h>
#include <Enum/DataIndexes.h>
#include <Enum/Pin.h>

#define DHT_TYPE DHT22

DHTService::DHTService(): dht(Pin::DHT22, DHT_TYPE)
{}

void DHTService::begin(){
    dht.begin();
}

float* DHTService::read(){
    static float data[2];
    data[TEMPERATURE] = constrain(dht.readTemperature(), -40.0, 80.0);
    data[HUMIDITY] = constrain(dht.readHumidity(), 0.0, 100.0);

    if (isnan(data[TEMPERATURE]) || isnan(data[HUMIDITY])) {
        data[TEMPERATURE] = 0;
        data[HUMIDITY] = 0;
        Serial.println("Не удалось считать данные с DHT22");
    }

    return data;
};