double lightLevel = 0.0;
 
#define SEND_DATA_DELAY 5000

#include "led.h"
#include "mqtt.h"


void setup() {
  Serial.begin(112500);
  InitMQTT();
  delay(1000);
 
  xTaskCreate(
                    globalIntTask,             /* Task function. */
                    "globalIntTask",           /* String with name of task. */
                    10000,                     /* Stack size in words. */
                    (void*)&lightLevel,      /* Parameter passed as input of the task */
                    1,                         /* Priority of the task. */
                    NULL);                     /* Task handle. */
 
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

void loop() {
  client.loop();
  // delay(1000);
}
 
void globalIntTask( void * parameter ){
    for(;;)  {
    Serial.print("globalIntTask: ");
    Serial.println(*((double*)parameter));            
    delay(2000);
    }
//    vTaskDelete( NULL );
 
}
 
void readLightTask( void * parameter ){
 for(;;)  {
    
    Serial.print("readLightTask: ");
    int sensorValueA3 = analogRead(A3);
    *((double*)parameter) = sensorValueA3 + 0.1;
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
    double message = *((double*)parameter);            
    client.publish(sensorTopic, String("Value:") + String(message));
    delay(5000);
    // vTaskDelay(5000);  // one tick delay (15ms) in between reads for stability
  }
}
