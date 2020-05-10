#include "tasks.h"


GenericData_t gdata = {1.1, 2.2, 3.3, 4.4, 5.6};


void CreateTasks() {
    xTaskCreate(
                readLightTask,              /* Task function. */
                "readLightTask",            /* String with name of task. */
                10000,                     /* Stack size in words. */
                (void*)&gdata,       /* Parameter passed as input of the task */
                1,                         /* Priority of the task. */
                NULL);                     /* Task handle. */
    xTaskCreate(
                readGasTask,              /* Task function. */
                "readGasTask",            /* String with name of task. */
                10000,                     /* Stack size in words. */
                (void*)&gdata,       /* Parameter passed as input of the task */
                1,                         /* Priority of the task. */
                NULL);                     /* Task handle. */
    xTaskCreate(
                readTemperatureTask,              /* Task function. */
                "readTemperatureTask",            /* String with name of task. */
                10000,                     /* Stack size in words. */
                (void*)&gdata,       /* Parameter passed as input of the task */
                1,                         /* Priority of the task. */
                NULL);

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
    delay(4000);
 }
}

void readGasTask( void * parameter ){
 for(;;)  {
    
    GenericData_t * mdata = (GenericData_t *) parameter;

    Serial.print("readGasTask: ");
    double gasValue = GetGasSensorValue();
    mdata->gas = gasValue;
    Serial.print("gas:");
    Serial.println(gasValue);
    delay(4000);
 }
}


void readTemperatureTask( void * parameter ){
 for(;;)  {
    
    GenericData_t * mdata = (GenericData_t *) parameter;

    Serial.print("readGasTask: ");
    double gasValue = GetGasSensorValue();
    mdata->temperature = gasValue;
    Serial.print("temperature:");
    Serial.println(gasValue);
    delay(4000);
 }
}


void sendDataTask(void *parameter) {

      // (void) pvParameters;
  for (;;)
  {
    client.loop();
  
//    String sensorTopic = "mytopic/test";
    String sensorTopic= "sdata";
    // double message = *((double*)parameter);
     GenericData_t * mdata = (GenericData_t *) parameter;
            
//    client.publish(sensorTopic, String("Value:") + String(mdata->light));
//    String msg = FormatDataJSON(mdata);
//    Serial.println(msg);

    String msg = "[" +CreateJSONItem("Light", mdata->light) + "]";
    client.publish(sensorTopic, msg);
    delay(500);
    
    msg = "[" + CreateJSONItem("Temperature", mdata->temperature ) + "]";
    client.publish(sensorTopic, msg);
    delay(300);

    msg = "[" + CreateJSONItem("Humidity", mdata->humidity ) + "]";
    client.publish(sensorTopic, msg);
    delay(300);
    
    msg = "[" + CreateJSONItem("Gas", mdata->gas ) + "]";
    client.publish(sensorTopic, msg);
    delay(300);


    msg = "[" + CreateJSONItem("Dust", mdata->dust ) + "]";
    client.publish(sensorTopic, msg);
    delay(300);
    
    delay(5000);
    // vTaskDelay(5000);  // one tick delay (15ms) in between reads for stability
  }
}
