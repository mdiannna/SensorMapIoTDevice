#include "tasks.h"
#include <Arduino.h>
#include "mqtt.h"
#include "format_data.h"

GenericData_t gdata = {0.0, 0.0, 0.0, 0.0, 0.0};

double lightlevel = 0;

void CreateTasks() {
	 xTaskCreate(
                    readLightTask,              /* Task function. */
                    "readLightTask",            /* String with name of task. */
                    10000,                     /* Stack size in words. */
                    (void*)&gdata,       /* Parameter passed as input of the task */
                    1,                         /* Priority of the task. */
                    NULL);                     /* Task handle. */
 
 xTaskCreate(
                    sendDataTask,              /* Task function. */
                    "sendDataTask",            /* String with name of task. */
                    10000,                     /* Stack size in words. */
                    (void*)&gdata,       /* Parameter passed as input of the task */
                    1,                         /* Priority of the task. */
                    NULL);                     /* Task handle. */
 
}


void readLightTask( void * parameter ){
 for(;;)  {
    
    GenericData_t * mdata = (GenericData_t *) parameter;

    Serial.print("readLightTask: ");
    double lightValue = GetLight();
    mdata->light = lightValue;
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
     GenericData_t * mdata = (GenericData_t *) parameter;
            
//    client.publish(sensorTopic, String("Value:") + String(mdata->light));
//    String msg = FormatDataJSON(mdata);
//    Serial.println(msg);

    String msg = "[" +CreateJSONItem("light", mdata->light) + "]";
    client.publish(sensorTopic, msg);
    delay(150);
    
    msg = "[" + CreateJSONItem("temperature", mdata->temperature ) + "]";
    client.publish(sensorTopic, msg);
    delay(150);


    msg = "[" + CreateJSONItem("humidity", mdata->humidity ) + "]";
    client.publish(sensorTopic, msg);
    delay(150);
    
    msg = "[" + CreateJSONItem("gas", mdata->gas ) + "]";
    client.publish(sensorTopic, msg);
    delay(150);


    msg = "[" + CreateJSONItem("dust", mdata->dust ) + "]";
    client.publish(sensorTopic, msg);
    delay(150);
    
    delay(5000);
    // vTaskDelay(5000);  // one tick delay (15ms) in between reads for stability
  }
}
