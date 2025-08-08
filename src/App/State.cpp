#include <App/State.h>


String serverUrl = "https://wstreet.systems";
bool serverAlive = false;
String token = "";
DeviceState deviceState = ACTIVE;
NetworkState networkState = DISCONNECTED;
unsigned long sleepModeStartTime = 0;
unsigned long lastDataUpdate = 0;