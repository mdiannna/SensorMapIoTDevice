
#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#define MCU1_ID 0x22
#define MCU2_ID 0x33

#define TYPE_HELLO 1
#define TYPE_QUERY_DATA 2
#define TYPE_SEND_DATA 3


#include <Arduino.h>

extern int data;

void CommunicationInit();
void SendHello();
void SendQueryData();
void SendPacket(char * message, uint8_t type); 
String ReceivePacket();


#endif
