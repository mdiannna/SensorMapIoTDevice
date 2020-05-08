#include "communication.h"
#include <Arduino.h>
#include <stdlib.h>
#include <Stream.h>
#include <string.h>


// Package structure:
/*
start package indicator
package counter (nr)
ID sender
ID receiver
type
<optional fields>
payload
checksum
end indicator
*/

// package number
uint8_t p_nr = 0;

String mystr;

void CommunicationInit() {
  Serial.begin(9600); 
}

int calculateChecksum(char * message, uint8_t type, uint8_t p_nr) {
  // return 13 + length(MY_ID) + length(RECEIVER_ID) + length(message) + length(type) + length(checksum);
    return 22 + strlen(message);
}

void SendPacket(char * message, uint8_t type) {
  Serial.print("STX");
  Serial.print(" ");
  if(p_nr < 10) {
    Serial.print("0");
  } else if(p_nr >99) {
    p_nr = 0;
  }
  Serial.print(p_nr++);
  Serial.print(" ");
  // Sender ID
  Serial.print(MCU2_ID, HEX);
  // Receiver ID
  Serial.print(" ");
  Serial.print(MCU1_ID, HEX);

  Serial.print(" ");
  Serial.print(type);
  Serial.print(" ");
  Serial.print(message);
  Serial.print(" ");

  int checksum = calculateChecksum(message, type, p_nr);
  Serial.print(checksum);

  Serial.print(" ");
  Serial.print("ETX");
}

  
String ReceivePacket() {
    int validPacket = 1;
    if(Serial.available() ){
    mystr = Serial.readString(); //Read the serial data and store in var
    Serial.println("--------------------------");
    Serial.println("----"+mystr+"----");
    Serial.println("--------------------------");

    size_t stx_pos = mystr.indexOf("STX");
    Serial.print("STX found at");
    Serial.print(stx_pos);

    if(stx_pos>2) {
      validPacket = 0;
      Serial.println();
      Serial.println("!!! PACKET NOT VALID !!!");
      Serial.println();
      return "-1";
    } 
    Serial.println();
    size_t etx_pos = mystr.indexOf("ETX");
    Serial.print("ETX found at");
    Serial.println(etx_pos);

    int messageLen = etx_pos+3;
    Serial.print("--Message length:");
    Serial.println(messageLen);

    if(messageLen-6 <0) {
      validPacket = 0;
      Serial.println("PACKET NOT VALID");
      return "-1";
    } 

    String checksum_s = mystr.substring(messageLen-6, messageLen-4);
    Serial.print("Checkum:");
    Serial.println(checksum_s);
    int checksum = checksum_s.toInt();
    Serial.println(checksum);

  if(checksum != messageLen) {
    validPacket = 0;
    Serial.println("PACKET NOT VALID");
    return "-1";
  }

  String message = mystr.substring(15, messageLen-7);
  Serial.println("MESSGE:");
  Serial.println(message);
  
  String packageCnt = mystr.substring(4, 6);
  Serial.print("Package counter");
  Serial.println(packageCnt);
  Serial.println(packageCnt.toInt());

  String type_s = mystr.substring(13, 15);
  Serial.print("Type:");
  Serial.println(type_s);
  int type = type_s.toInt();
  Serial.println(type);
  // return type;
  return message;
  }
  else {
    return "-2";
  }
}



void SendHello() {
  SendPacket("Hello!", TYPE_HELLO);
}
