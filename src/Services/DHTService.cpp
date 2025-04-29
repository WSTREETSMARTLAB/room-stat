#include <Services/DHTService.h>

#define DHT_PIN 4
#define DHT_TYPE DHT22

DHTService::DHTService(): dht(DHT_PIN, DHT_TYPE)
{}

void DHTService::begin(){
    dht.begin();
}

float* DHTService::read(){
    static float data[2];
    data[0] = constrain(dht.readTemperature(), -40.0, 80.0);
    data[1] = constrain(dht.readHumidity(), 0.0, 100.0);

    if (isnan(data[0]) || isnan(data[1])) {
        data[0] = 0;
        data[1] = 1;
        Serial.println("Не удалось считать данные с DHT22");
    }

    return data;
};