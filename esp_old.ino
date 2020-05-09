
#include <Arduino.h>
#include "communication.h"
#include <Wire.h>
#include "led.h"


/*
  SimpleMQTTClient.ino
  The purpose of this exemple is to illustrate a simple handling of MQTT and Wifi connection.
  Once it connects successfully to a Wifi network and a MQTT broker, it subscribe to a topic and send a message to it.
  It will also send a message delayed 5 seconds later.
*/

#include "EspMQTTClient.h"


#define WSSID "MTC_B45"
#define WPASSWORD "Q91L2I2000257"
#define MQTT_SERVER "broker.hivemq.com"

#define SEND_DATA_DELAY 5000

String sensorTopic = "mytopic/test";
int connection_established_arduino = 0;
String message = "Hello!";

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
	LED_Init();
	CommunicationInit();
	InitMQTT();

	Serial.println("Init done ESP");
	delay(1000);
	SendHello();
}

void loop() {
	LED_Off();
  client.loop();
  message  = ReceivePacket();
 // Serial.println("---=====Received command:=====---");
  //Serial.println(message);
  
  if(message != "-2" && message != "") {
  	connection_established_arduino = 1;
  }

  if(connection_established_arduino !=1) {
  	SendHello();	
  } else {
    SendQueryData();
    if(message != "-2") {
    	LED_On();
  	  client.publish(sensorTopic, message); // You can activate the retain flag by setting the third parameter to true
    }
  }

	delay(SEND_DATA_DELAY);
}
