#include <Wire.h>
#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
#include "ThingSpeak.h"
//----------- Enter you Wi-Fi Details---------//
char ssid[] = ""; //SSID
char pass[] = ""; // Password
//-------------------------------------------//

const int trigger = 16;
const int echo = 5;
long T;
float xd,yd,zd;
float distance;
WiFiClient  client;

unsigned long myChannelField = ; // Channel ID
const int ChannelField1 = 1;// Which channel to write data
const int ChannelField2= 2;
const int ChannelField3 = 3;
const char * myWriteAPIKey = ""; // Your write API Key
void setup() 
{
  Serial.begin(115200);  
  if(!accel.begin())
  {
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
    
  }
  accel.setRange(ADXL345_RANGE_4_G);
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

  sensors_event_t event; 
  accel.getEvent(&event);
 
  Serial.print((event.acceleration.x)/9.8); Serial.print(",");
  Serial.print((event.acceleration.y)/9.8); Serial.print(",");
  Serial.println((event.acceleration.z)/9.8);
  delay(10);
  xd=(event.acceleration.x)/9.8;
  yd=(event.acceleration.y)/9.8;
  zd=(event.acceleration.z)/9.8;
  ThingSpeak.writeField(myChannelField, ChannelField1, xd, myWriteAPIKey);
   ThingSpeak.writeField(myChannelField, ChannelField2, yd, myWriteAPIKey);
    ThingSpeak.writeField(myChannelField, ChannelField3, zd, myWriteAPIKey);
  delay(1000);



  
}
