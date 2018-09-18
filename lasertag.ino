#include "spikesensor.h"

SpikeSensor spikeSensor;

void setup() {
  Serial.begin(115200);
  //Pulse laser at 4hz for testing
  tone(A0, 4);
}

void loop() {
  int spike = spikeSensor.addReading(analogRead(A2), millis());
  if(spike > 0){
    Serial.println(spike);
  }
}
