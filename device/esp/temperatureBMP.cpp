#include "temperatureBMP.h"
#include <Arduino.h>
#include <Wire.h>

// Sparkfun BMP180 library
#include "SFE_BMP180.h"


SFE_BMP180 sensor;

void InitTemperatureSensorBMP()
{
  if (sensor.begin())
    Serial.println("Temperature sensor init success");
  else
  {
    Serial.println("Temperature sensr PMB180 init fail\n\n");
    // while(1); // Pause forever.
  }
}


double GetTemperatureBMP(){
  char status;
  double T;

  status = sensor.startTemperature();
    if (status != 0)
    {
      // Wait for the measurement to complete:
      delay(status);

      // Retrieve the completed temperature measurement:
      // The measurement is stored in the variable T.
      // Function returns 1 if successful, 0 if failure.

      status = sensor.getTemperature(T);
      if (status != 0)
      {
        // Print out the measurement:
        // Serial.print("temperature: ");
        // Serial.print(T,2);
        // Serial.print(" deg C, ");
      }
      // TODO: printf?
      else Serial.println("error retrieving temperature measurement\n");
    }
    else Serial.println("error starting temperature measurement\n");

    return T;
}