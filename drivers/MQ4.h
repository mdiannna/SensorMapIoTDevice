#ifndef _MQ4_H_
#define _MQ4_H_

#include <MQUnifiedsensor.h>
/************************Hardware Related Macros************************************/
#define         Board                   ("Arduino UNO")
#define         Pin                     (A3)  //Analog input 3 of your arduino
/***********************Software Related Macros************************************/
#define         Type                    ("MQ-3") //MQ3
#define         Voltage_Resolution      (5)
#define         ADC_Bit_Resolution      (10) // For arduino UNO/MEGA/NANO

void InitMQ4();
float GetMQ4();

#endif
