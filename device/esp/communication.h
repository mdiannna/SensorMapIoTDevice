
#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#define MCU1_ID 0x22
#define MCU2_ID 0x33

#define TYPE_HELLO 1
#define TYPE_QUERY_DATA_I2C 2
#define COMMAND_SEND_SENSOR_DATA 2
#define SENSOR_DATA_CM 3

#include <Arduino.h>

extern int data;

void CommunicationInit();
void SendHello();
void SendPacket(char * message, uint8_t type); 
String ReceivePacket();


#endif
