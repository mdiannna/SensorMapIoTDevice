#include "led.h"
#include <Arduino.h>

void LED_Init() {
// pinMode(LED_PIN, INPUT_PULLUP);
	pinMode(LED_PIN, OUTPUT);
	pinMode(GREEN_LED_PIN, OUTPUT);
	pinMode(RED_LED_PIN, OUTPUT);
}

int Is_LED_On() {
	int LEDState = digitalRead(LED_PIN);
	if(LEDState==LED_ON) {
		return 1;
	}
//else
	return 0;
}

void LED_On() {
	digitalWrite(LED_PIN, LED_ON);
}

void Red_LED_On() {
	digitalWrite(RED_LED_PIN, LED_ON);
}

void Green_LED_On() {
	digitalWrite(GREEN_LED_PIN, LED_ON);
}

void LED_Off() {
	digitalWrite(LED_PIN, LED_OFF);
}

void Red_LED_Off() {
	digitalWrite(RED_LED_PIN, LED_OFF);
}

void Green_LED_Off() {
	digitalWrite(GREEN_LED_PIN, LED_OFF);
}
