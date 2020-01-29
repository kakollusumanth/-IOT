#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
  
//----------- Enter you Wi-Fi Details---------//
char ssid[] = "xxxxxxxx"; //SSID
char pass[] = "xxxxxxxxx"; // Password
//-------------------------------------------//

const int trigger = 16;
const int echo = 5;
long T;
float distance;
WiFiClient  client;

unsigned long myChannelField = xxxx; // Channel ID
const int ChannelField = 1; // Which channel to write data
const char * myWriteAPIKey = "xxxxxxxxxxxxxxx"; // Your write API Key

void setup()
{
  Serial.begin(115200);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}
void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
  digitalWrite(trigger, LOW);
  delay(1);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  T = pulseIn(echo, HIGH);
  distance = T * 0.034;
  distance = distance / 2;
  Serial.print("Distance in cm: ");
  Serial.println(distance);
  ThingSpeak.writeField(myChannelField, ChannelField, distance, myWriteAPIKey);
  delay(1000);
}
