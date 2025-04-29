#include <Processes/DataCollectingProcess.h>
#include <Enum/DataIndexes.h>

DataCollectingProcess::DataCollectingProcess(DHTService& dht)
: dht(dht)
{}

DataConfig DataCollectingProcess::handle(){
    DataConfig data;

    static float* dhtSensorData;
    dhtSensorData = dht.read();

    data.temperature = dhtSensorData[TEMPERATURE];
    data.humidity = dhtSensorData[HUMIDITY];

    return data;
}