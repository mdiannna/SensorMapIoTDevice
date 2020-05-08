
#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#define MCU1_ID 0x22
#define MCU2_ID 0x33

#define TYPE_HELLO 2
#define TYPE_QUERY_DATA 1
#define COMMAND_SEND_SENSOR_DATA 1
#define TYPE_SEND_DATA 4	
#define SENSOR_DATA_CM 3

#include <Arduino.h>


extern int data;

void CommunicationInit();
void SendHello();
void SendPacket(String message, uint8_t type); 
void SendPacket(String message, uint8_t type); 
int ReceivePacket();


#endif
