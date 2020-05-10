#ifndef _MQTT_H_
#define _MQTT_H_

#include "EspMQTTClient1.h"

#define WSSID "MTC_B45"
#define WPASSWORD "Q91L2I2000257"
//#define MQTT_SERVER "broker.hivemq.com"

//#define MQTT_SERVER "mqtt+ssl://b-cf947f7f-da66-44d1-b85c-66b5bec7b7ee-1.mq.us-east-2.amazonaws.com"
#define MQTT_SERVER "b-cf947f7f-da66-44d1-b85c-66b5bec7b7ee-1.mq.us-east-2.amazonaws.com"
#define MQTT_PORT  8883 
//1883              // The MQTT port, default to 1883. this line can be omitted
#define USER "admin"
#define PASSWORD "N94g5b85YrCX"
 

extern EspMQTTClient client;
void InitMQTT();

void onConnectionEstablished();

#endif
