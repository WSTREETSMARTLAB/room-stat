#include <Processes/DataCollectingProcess.h>
#include <Enum/DataIndexes.h>
#include <App/State.h>

DataCollectingProcess::DataCollectingProcess(DHTService& dht, LDRService& ldr, PowerManager& power)
: dht(dht), ldr(ldr), power(power)
{}

DataConfig DataCollectingProcess::handle(unsigned long currentTime){
    DataConfig data;
    static float* dhtSensorData;
    dhtSensorData = dht.read();

    data.temperature = dhtSensorData[TEMPERATURE];
    data.humidity = dhtSensorData[HUMIDITY];
    data.light = ldr.read();

    lastDataUpdate = currentTime;
    nextDataUpdate = currentTime + power.getDataTransmittingDelay();

    return data;
}