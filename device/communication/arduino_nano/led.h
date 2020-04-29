////////////////////////////////////////
// Led
////////////////////////////////////////
//led.h
// builtin pin is 13 - LED_BUILTIN

#ifndef LED_H_
#define LED_H_

#define LED_PIN 2 // change
#define RED_LED_PIN 11 // change
#define GREEN_LED_PIN 12 // change
#define LED_ON 1
#define LED_OFF 0

void LED_Init();
int Is_LED_On();
void LED_On();
void LED_Off();

void Red_LED_On();
void Green_LED_On();
void LED_Off();
void Red_LED_Off();
void Green_LED_Off();
////
#endif
