/*
 *  This sketch sends a message to a TCP server
 *https://github.com/wemos/Arduino_ESP32/blob/master/docs/arduino-ide/windows.md
 */

#include <WiFi.h>
#include <WiFiMulti.h>

#define SSID1 "MTC_B45"
#define PASSWORD "Q91L2I2000257"

WiFiMulti WiFiMulti;

void setup()
{
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network
    WiFiMulti.addAP(SSID1, PASSWORD);

    Serial.println();
    Serial.println();
    Serial.print("Waiting for WiFi... ");

    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(500);
}


void loop()
{
    const uint16_t port = 5000;
    const char * host = "192.168.0.79"; // ip or dns
//    const char * host = "192.168.1.1"; // ip or dns
//    const uint16_t port = 1337;
//    const char * host = "192.168.1.10"; // ip or dns

    Serial.print("Connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;

    if (!client.connect(host, port)) {
        Serial.println("Connection failed.");
        Serial.println("Waiting 5 seconds before retrying...");
        delay(5000);
        return;
    }

    // This will send a request to the server
    //uncomment this line to send an arbitrary string to the server
    //client.print("Send this data to the server");
    //uncomment this line to send a basic document request to the server
//    client.print("GET /hello-esp HTTP/1.1\n\n");
    client.print("POST /esp-test-post HTTP/1.1\n\n");

  int maxloops = 0;

  //wait for the server's reply to become available
  while (!client.available() && maxloops < 1000)
  {
    maxloops++;
    delay(1); //delay 1 msec
  }
  if (client.available() > 0)
  {
    //read back one line from the server
    String line = client.readStringUntil('\r');
    Serial.println(line);
  }
  else
  {
    Serial.println("client.available() timed out ");
  }

    Serial.println("Closing connection.");
    client.stop();

    Serial.println("Waiting 5 seconds before restarting...");
    delay(5000);
}