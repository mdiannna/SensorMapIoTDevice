#include "format_data.h"
#define DEVICE_ID 1

String CreateJSONItem(String sensorType, double value) {
  String result = " { \"boxID\": "+ String(DEVICE_ID)
  + ", \"sensorType\": \"" + String(sensorType) +"\" " +
  + ",\"value\": " + String(value) + "}"; 
 
  return result;
}


String FormatDataJSON(Data_t * ffdata) {
  String result = "[" 
  + CreateJSONItem("temperature", ffdata->temperature) + "," 
  + CreateJSONItem("humidity", ffdata->humidity)+ ","
  + CreateJSONItem("light", ffdata->light) + ","
  + CreateJSONItem("gas", ffdata->gas) + ","
  + CreateJSONItem("dust", ffdata->dust) + ","
  + "]";
  return result;
}
