#include <App/State.h>

String serverUrl = "https://wstreet.systems";
bool serverAlive = false;
String token = "";
DeviceState currentDeviceState = ACTIVE;
unsigned long lastActivityTime = 0;
unsigned long sleepModeStartTime = 0;