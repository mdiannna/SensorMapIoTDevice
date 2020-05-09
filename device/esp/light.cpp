#include "light.h"

void InitLight() {
  pinMode(LDR_PIN, INPUT);
}

double GetLight() {
  int value = analogRead(LDR_PIN);
  double voltage = value * (5.0 / 1024.0);
	return voltage;
}
