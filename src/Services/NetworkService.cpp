#include <Services/NetworkService.h>

NetworkService::NetworkService(
    WiFiPointManager& wifi,
    AccessPointManager& accessPoint
)
    : state(NetworkState::DISCONNECTED)
    , stateStart(millis())
    , lastCheck(0) {}

void NetworkService::update(){
    unsigned long currentTime = millis();
    
    if (currentTime - lastCheck >= CHECK_INTERVAL) {
        evaluateState();
        lastCheck = currentTime;
    }
}

void NetworkService::attemptConnection(const String& ssid, const String& password){
    if (state == NetworkState::CONNECTING || state == NetworkState::RECONNECTING) {
        return;
    }

    wifi.connect(ssid, password);
}

void NetworkService::startAP(){
    
}

void NetworkService::forceReconnection(){

}

void NetworkService::reset(){

}

void NetworkService::evaluateState(){
    NetworkState state = state;

    switch (state)
    {
    case NetworkState::DISCONNECTED:
        break;
    case NetworkState::RECONNECTING:
        
    case NetworkState::AP_MODE:
    case NetworkState::ERROR:
        break;
    
    default:
        break;
    }
}

void NetworkService::transitionTo(NetworkState newState){
    state = newState;
    stateStart = millis();
}