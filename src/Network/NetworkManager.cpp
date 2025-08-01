#include <Network/NetworkManager.h>

NetworkManager::NetworkManager(DisplayService& display)
    : state(NetworkState::DISCONNECTED)
    , stateStart(millis())
    , lastCheck(0) {}

void NetworkManager::update(){

}

void NetworkManager::attemptConnection(const String& ssid, const String& password){

}

void NetworkManager::startAP(){

}

void NetworkManager::forceReconnection(){

}

void NetworkManager::reset(){

}