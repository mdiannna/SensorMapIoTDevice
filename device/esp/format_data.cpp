#include "format_data.h"
#define DEVICE_ID 1

String CreateJSONItem(String sensorType, double value) {
  String result = "{ \"boxId\": "+ String(DEVICE_ID)
  + ", \"sensorType\": \"" + String(sensorType) +"\" " +
  + ",\"sensorValue\": " + String(value) + "}"; 
 
  return result;
}


String FormatDataJSON(Data_t * ffdata) {
  String result = "[" 
  + CreateJSONItem("Temperature", ffdata->temperature) + "," 
  + CreateJSONItem("Humidity", ffdata->humidity)+ ","
  + CreateJSONItem("Light", ffdata->light) + ","
  + CreateJSONItem("Gas", ffdata->gas) + ","
  + CreateJSONItem("Dust", ffdata->dust) + ","
  + "]";
  return result;
}
