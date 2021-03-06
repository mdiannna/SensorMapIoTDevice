#include "MQ4.h"

//Declare Sensor
#define placa "Arduino UNO"
#define Voltage_Resolution 5
#define pin A4 //Analog input 4 of your arduino
#define type "MQ-4" //MQ4
#define ADC_Bit_Resolution 10 // For arduino UNO/MEGA/NANO
#define RatioMQ4CleanAir 4.4  //RS / R0 = 4.4 ppm 
//#define calibration_button 13 //Pin to calibrate your sensor

//Declare Sensor
MQUnifiedsensor MQ4(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);

void InitMQ4() {
float calcR0 = 0;
  for(int i = 1; i<=10; i ++)
  {
    MQ4.update(); // Update data, the arduino will be read the voltage on the analog pin
    calcR0 += MQ4.calibrate(RatioMQ4CleanAir);
    Serial.print(".");
  }
  MQ4.setR0(calcR0/10);
  Serial.println("  done!.");
  
  if(isinf(calcR0)) {Serial.println("Warning: Conection issue founded, R0 is infite (Open circuit detected) please check your wiring and supply"); while(1);}
  if(calcR0 == 0){Serial.println("Warning: Conection issue founded, R0 is zero (Analog pin with short circuit to ground) please check your wiring and supply"); while(1);}
  /*****************************  MQ CAlibration ********************************************/ 

  /* 
    //If the RL value is different from 10K please assign your RL value with the following method:
    MQ4.setRL(10);
  */

  /*****************************  MQ Init ********************************************/ 
  //Input: setup flag, if this function are on setup will print the headers (Optional - Default value: False)
  //Output: print on serial port the information about sensor and sensor readings
  //Remarks: Configure the pin of arduino as input.
  /************************************************************************************/ 
  MQ4.init(); 
}

float GetMQ4() {

    MQ4.update(); // Update data, the arduino will be read the voltage on the analog pin
  
  //https://jayconsystems.com/blog/understanding-a-gas-sensor 
  //Set math model to calculate the PPM concentration and the value of constants
  MQ4.setRegressionMethod(0); //_PPM =  pow(10, (log10(ratio)-b)/a)
  MQ4.setA(-0.318); MQ4.setB(1.133); // A -> Slope, B -> Intersect with X - Axis
  float LPG1 = MQ4.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup
  
  //Set math model to calculate the PPM concentration and the value of constants
  MQ4.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ4.setA(1012.7); MQ4.setB(-2.786); // Configurate the ecuation values to get CH4 concentration
  float LPG2 = MQ4.readSensor();
  return LPG2;
}
