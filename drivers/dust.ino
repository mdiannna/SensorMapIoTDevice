#include "dust.h"

DustSensor sensor = DustSensor(A1, 13);

void setup(){
  Serial.begin(9600);
}

void loop(){

 SensorData data = sensor.read();

  Serial.println("Raw Signal Value (0-1023):");
  Serial.println(data.voMeasured);

  Serial.println("Voltage:");
  Serial.println(data.calcVoltage);

  Serial.println("Dust Density:");
  Serial.println(data.dustDensity);
  Serial.println();

  delay(1000);
}
