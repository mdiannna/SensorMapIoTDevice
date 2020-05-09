#include "tasks.h"
#include <Arduino.h>
#include "mqtt.h"

GenericData_t data = {0.0, 0.0, 0.0, 0.0, 0.0};

double lightlevel = 0;

void CreateTasks() {
	 xTaskCreate(
                    readLightTask,              /* Task function. */
                    "readLightTask",            /* String with name of task. */
                    10000,                     /* Stack size in words. */
                    (void*)&data,       /* Parameter passed as input of the task */
                    1,                         /* Priority of the task. */
                    NULL);                     /* Task handle. */
 
 xTaskCreate(
                    sendDataTask,              /* Task function. */
                    "sendDataTask",            /* String with name of task. */
                    10000,                     /* Stack size in words. */
                    (void*)&data,       /* Parameter passed as input of the task */
                    1,                         /* Priority of the task. */
                    NULL);                     /* Task handle. */
 
}


void readLightTask( void * parameter ){
 for(;;)  {
    
    GenericData_t * data = (GenericData_t *) parameter;

    Serial.print("readLightTask: ");
    double lightValue = GetLight();
    data->light = lightValue;
    Serial.println(lightValue);
    delay(5000);
 }
}


void sendDataTask(void *parameter) {

      // (void) pvParameters;
  for (;;)
  {
    String sensorTopic = "mytopic/test";
    // double message = *((double*)parameter);
     GenericData_t * data = (GenericData_t *) parameter;
            
    client.publish(sensorTopic, String("Value:") + String(data->light));
    delay(5000);
    // vTaskDelay(5000);  // one tick delay (15ms) in between reads for stability
  }
}
