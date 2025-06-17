#include <Processes/DataCollectingProcess.h>
#include <Enum/DataIndexes.h>

DataCollectingProcess::DataCollectingProcess(DHTService& dht, LDRService& ldr)
: dht(dht), ldr(ldr)
{}

DataConfig DataCollectingProcess::handle(){
    DataConfig data;

    static float* dhtSensorData;
    dhtSensorData = dht.read();

    data.temperature = dhtSensorData[TEMPERATURE];
    data.humidity = dhtSensorData[HUMIDITY];
    data.light = ldr.read();

    return data;
}