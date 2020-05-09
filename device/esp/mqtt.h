#ifndef _MQTT_H_
#define _MQTT_H_

#include "EspMQTTClient.h"

#define WSSID "MTC_B45"
#define WPASSWORD "Q91L2I2000257"
#define MQTT_SERVER "broker.hivemq.com"

extern EspMQTTClient client;
void InitMQTT();

void onConnectionEstablished();

#endif
