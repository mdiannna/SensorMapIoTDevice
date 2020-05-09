#include "LDR.h"

int ldrPin = A0;

void setup() {
  pinMode(ldrPin, INPUT);
  Serial.begin(9600);
  Serial.println(F("LDR test"));
}

void loop() {
  int Value = analogRead(ldrPin);
  Serial.print("LDR: ");
  Serial.println(Value);
  delay(200);
}
