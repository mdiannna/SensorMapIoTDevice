#ifndef _FORMAT_DATA_H_
#define _FORMAT_DATA_H_

#include <Arduino.h>

typedef struct Data_t
{
    // uint32_t ucData;
    // char id;
    double light;
    double temperature;
    double humidity;
    double dust;
    double gas;
} GenericData_t;


String CreateJSONItem(String sensorType, double value);
String FormatDataJSON(Data_t *ffdata);

#endif
