double lightLevel = 0.0;
 #define WSSID "MTC_B45"
#define WPASSWORD "Q91L2I2000257"
#define MQTT_SERVER "broker.hivemq.com"

#define SEND_DATA_DELAY 5000

#include "led.h"
#include "EspMQTTClient.h"


String sensorTopic = "mytopic/test";
int connection_established_arduino = 0;

EspMQTTClient client(
  WSSID,
  WPASSWORD,
  MQTT_SERVER,  // MQTT Broker server ip
  "",   // Can be omitted if not needed username
  "",   // Can be omitted if not needed password
  "TestClient",     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted
);

void InitMQTT() {
  // Optionnal functionnalities of EspMQTTClient : 
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overrited with enableHTTPWebUpdater("user", "password").
  client.enableLastWillMessage("TestClient/lastwill", "I am going offline");  // You can activate the retain flag by setting the third parameter to true
}

// This function is called once everything is connected (Wifi and MQTT)
// WARNING : YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient
void onConnectionEstablished()
{
  // Subscribe to "mytopic/test" and display received message to Serial
  client.subscribe(sensorTopic, [](const String & payload) {
  LED_On();
    //Serial.println(payload);
  });

  // Subscribe to "mytopic/wildcardtest/#" and display received message to Serial
  // client.subscribe("mytopic/wildcardtest/#", [](const String & topic, const String & payload) {
  //   Serial.println(topic + ": " + payload);
  // });

  // Publish a message to "mytopic/test"
  client.publish(sensorTopic, "Hello--"); // You can activate the retain flag by setting the third parameter to true

  // Execute delayed instructions
  // client.executeDelayed(5 * 1000, []() {
  //   client.publish("mytopic/test", "This is a message sent 5 seconds later");
  // });
}



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
                    readSensorTask,              /* Task function. */
                    "readSensorTask",            /* String with name of task. */
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
 
void readSensorTask( void * parameter ){
 for(;;)  {
    
    Serial.print("readSensorTask: ");
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
    double message = *((double*)parameter);            
    client.publish(sensorTopic, String("Value:") + String(message));
    delay(5000);
    // vTaskDelay(5000);  // one tick delay (15ms) in between reads for stability
  }
}
