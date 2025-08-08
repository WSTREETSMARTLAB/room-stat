#include <Services/NetworkService.h>

NetworkService::NetworkService(
    WiFiPointManager& wifi,
    AccessPointManager& accessPoint
)
    : state(NetworkState::DISCONNECTED)
    , stateStart(millis())
    , lastCheck(0)
    , wifi(wifi)
    , accessPoint(accessPoint)
    , reconnectionAttempts(0)
 {}

void NetworkService::update(unsigned long currentTime){    
    if (currentTime - lastCheck >= CHECK_INTERVAL) {
        evaluateState(currentTime);
        lastCheck = currentTime;
    }
}

void NetworkService::attemptConnection(const String& ssid, const String& password){
    while (networkState != CONNECTED && reconnectionAttempts < MAX_RECONNECTION_ATTEMPTS) {
        wifi.connect(ssid, password);
        
        if (wifi.isConnected()) {
            networkState = CONNECTED;
            reconnectionAttempts = 0;
            break;
        } else {
            networkState = ERROR;
            wifi.disconnect();
            reconnectionAttempts++;
            delay(500);
        }
    }
}

void NetworkService::startAP(){
    if (networkState == AP_MODE) {
        return;
    }
    
    accessPoint.begin("Room_Stat_Access", "");
    networkState = AP_MODE;
}

void NetworkService::evaluateState(unsigned long currentTime){
    NetworkState newState = networkState;

    if (networkState == CONNECTED){
        if (!wifi.isConnected()){
            newState = DISCONNECTED;
        }
    }

    if (networkState == ERROR || networkState == DISCONNECTED){
        if (wifi.isConnected()){
            newState = CONNECTED;
        }
    }    

    if (newState != state) {
        networkState = newState;
        stateStart = currentTime;
    }
}