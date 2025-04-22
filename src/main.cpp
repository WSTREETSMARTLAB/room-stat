#include <Arduino.h>
#include <App/App.h>

App app;

void setup() {
  Serial.begin(115200);
  delay(2000);
  
  app.setup();
}

void loop() {
  app.loop();
  delay(2000);
}