/** Voice controlled house lights with Google Assitant
 *  Instructable contest
 *  Mridul Mahajan
 */
/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

 */
#define BLYNK_PRINT Serial
#define EspSerial Serial1

#include <SoftwareSerial.h>
#include<SPI.h>
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// You should get Auth Token in the Blynk App.
char auth[] = "68O8QXywAHetPvqMhh0iH56GYVDbX2IQ";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "yonginDT";
char pass[] = "12345678";


SoftwareSerial EspSerial(2, 3); // RX, TX of ESP8266

String s,x;    //to store incoming text ingredient

BLYNK_WRITE(V0)     // it will run every time a string is sent by Blynk app
{
  s=param.asStr();
  Serial.print(s); //string sent by Blynk app will be printed on Serial Monitor
   if(s=="on")
  {
    digitalWrite(7, LOW);       //Pin 7 has been set in setup()
//    digitalWrite(8, LOW);       //Pin 7 has been set in setup()
  }
  else if(s=="off")
  {
    digitalWrite(7, HIGH);
//    digitalWrite(8, HIGH);
    
  }
  else{
    Serial.print("Say on or off");
  }
}
BLYNK_WRITE(V1)     // it will run every time a string is sent by Blynk app
{
  x=param.asStr();
  Serial.print(x); //string sent by Blynk app will be printed on Serial Monitor
   if(x=="on")
  {
//    digitalWrite(7, LOW);       //Pin 7 has been set in setup()
    digitalWrite(8, LOW);       //Pin 7 has been set in setup()
  }
  else if(x=="off")
  {
//    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    
  }
  else{
    Serial.print("Say on or off");
  }
}

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(7,OUTPUT);       //Pin 7 is set to output
  pinMode(8,OUTPUT);       //Pin 8 is set to output
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
 
  Blynk.begin(auth, wifi, ssid, pass);
}

void loop()
{
  Blynk.run();
}
