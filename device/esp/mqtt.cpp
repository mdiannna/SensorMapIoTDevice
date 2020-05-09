#include "mqtt.h"

#include "led.h"

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



void InitMQTT() {
  // Optionnal functionnalities of EspMQTTClient : 
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overrited with enableHTTPWebUpdater("user", "password").
  client.enableLastWillMessage("TestClient/lastwill", "I am going offline");  // You can activate the retain flag by setting the third parameter to true
}
