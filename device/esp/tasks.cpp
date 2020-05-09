#include "tasks.h"
#include <Arduino.h>
#include "mqtt.h"

GenericData_t data = {0.0, 0.0};

double lightlevel = 0;

void CreateTasks() {
	 xTaskCreate(
                    readLightTask,              /* Task function. */
                    "readLightTask",            /* String with name of task. */
                    10000,                     /* Stack size in words. */
                    (void*)&lightLevel,       /* Parameter passed as input of the task */
                    1,                         /* Priority of the task. */
                    NULL);                     /* Task handle. */
 
 xTaskCreate(
                    sendDataTask,              /* Task function. */
                    "sendDataTask",            /* String with name of task. */
                    10000,                     /* Stack size in words. */
                    (void*)&lightLevel,       /* Parameter passed as input of the task */
                    1,                         /* Priority of the task. */
                    NULL);                     /* Task handle. */
 
}


void readLightTask( void * parameter ){
 for(;;)  {
    
    GenericData_t * data = (GenericData_t *) parameter;

    Serial.print("readLightTask: ");
    int sensorValueA3 = analogRead(A3);
    data->light = sensorValueA3 + 0.1;
    Serial.println(sensorValueA3);
    delay(5000);
 }
//    vTaskDelete( NULL );
 
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
