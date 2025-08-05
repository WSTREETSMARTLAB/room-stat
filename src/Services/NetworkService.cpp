#include <Services/NetworkService.h>

NetworkService::NetworkService(
    WiFiPointManager& wifi,
    AccessPointManager& accessPoint,
    DisplayManager& display
)
    : state(NetworkState::DISCONNECTED)
    , stateStart(millis())
    , lastCheck(0)
    , wifi(wifi)
    , accessPoint(accessPoint)
    , display(display)
    , reconnectionAttempts(0)
    , totalConnectionAttempts(0)
    , successfulConnections(0)
    , lastSuccessfulConnection(0) {}

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

    state = NetworkState::CONNECTING;
    display.loader([this]() { return wifi.isConnected(); }, "Connecting to WiFi...");
    wifi.connect(ssid, password);

    if (wifi.isConnected){
        state = NetworkState::CONNECTED;
    }
}

void NetworkService::startAP(){
    if (state == NetworkState::AP_MODE) {
        return;
    }
    
    accessPoint.begin("Room_Stat_Access", "");
    state = NetworkState::AP_MODE;

}

void NetworkService::forceReconnection(){
    //
}

void NetworkService::reset(){
    //
}

void NetworkService::evaluateState(){
    NetworkState newState = state;

    switch (state)
    {
    case NetworkState::DISCONNECTED:   
        break;
    case NetworkState::CONNECTING:
        if (getTimeInCurrentState() > CONNECTION_TIMEOUT) {
            newState = NetworkState::RECONNECTING;
            updateMetrics(false);
        } else if (wifi.isConnected()) {
            newState = NetworkState::CONNECTED;
            updateMetrics(true);
        }
        break;
    case NetworkState::CONNECTED:
        if (!wifi.isConnected()) {
            newState = NetworkState::RECONNECTING;
        }
        break;
    case NetworkState::RECONNECTING:
        if (getTimeInCurrentState() > RECONNECT_TIMEOUT) {
            if (reconnectionAttempts >= MAX_RECONNECTION_ATTEMPTS) {
                newState = NetworkState::AP_MODE;
            } else {
                reconnectionAttempts++;
                stateStart = millis();
            }
            } else if (wifi.isConnected()) {
                newState = NetworkState::CONNECTED;
                updateMetrics(true);
                reconnectionAttempts = 0;
            }
        break;
    case NetworkState::AP_MODE:        
        break;
    case NetworkState::ERROR:
        break;
    default:
        break;
    }

    if (newState != state) {
        transitionTo(newState);
    }
}

void NetworkService::transitionTo(NetworkState newState){
    state = newState;
    stateStart = millis();
}

unsigned long NetworkService::getTimeInCurrentState() const {
    return millis() - stateStart;
}

NetworkState NetworkService::getCurrentState() const {
    return state;
}

void NetworkService::updateMetrics(bool connectionSuccess){
    if (connectionSuccess) {
        successfulConnections++;
        lastSuccessfulConnection = millis();
    }
}