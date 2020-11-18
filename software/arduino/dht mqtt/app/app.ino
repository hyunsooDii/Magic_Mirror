#include "WifiUtil.h"
#include <PubSubClient.h>
#include "DHT.h"          // Librairie des capteurs DHT
WifiUtil wifi(2, 3);

const char SSID[] = "yonginDT";
const char PASSWORD[] = "12345678";

#define mqtt_server "192.168.137.176"
#define mqtt_user "localhost"      // if exist
#define mqtt_password ""  //idem

#define temperature_topic "iot/temperature"  //Topic temperature
#define humidity_topic "iot/humidity"        //Topic humidity

//Buffer to decode MQTT messages
char message_buff[100];

long lastMsg = 0;   
long lastRecu = 0;
bool debug = false;  //Display log message if True

#define DHTPIN A3    // DHT Pin 
#define HEATER1 A2    // Heater Led Pin
#define HEATER2 13

// Un-comment you sensor
#define DHTTYPE DHT11       // DHT 11 

// Create abjects
DHT dht(DHTPIN, DHTTYPE);     
WiFiEspClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);
  wifi.init(SSID, PASSWORD);     
//  setup_wifi();           //Connect to Wifi network
  client.setServer(mqtt_server, 1883);    // Configure MQTT connexion
  client.setCallback(callback);           // callback function to execute when a MQTT message   
  pinMode(HEATER1,OUTPUT);
  pinMode(HEATER2,OUTPUT);
  dht.begin();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT broker ...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("OK");
    } else {
      Serial.print("KO, error : ");
      Serial.print(client.state());
      Serial.println(" Wait 5 secondes before to retry");
      delay(5000);
    }
  }
}

void loop() {
  if (wifi.check())
  { // WIFI 연결 확인
      ;
  }
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  // Send a message every minute
  if (now - lastMsg > 2000) {
    lastMsg = now;
    // Read humidity
    float h = dht.readHumidity();
    // Read temperature in Celcius
    float t = dht.readTemperature();

    // Oh, nothing to send
    if ( isnan(t) || isnan(h)) {
      Serial.println("Please check DHT sensor !");
      return;
    }
    
    if(h < 25.50) {
        digitalWrite(HEATER1, HIGH);
        digitalWrite(HEATER2, HIGH);
    } else {
        digitalWrite(HEATER1, LOW);
        digitalWrite(HEATER2, LOW);
    }
  
      Serial.print("Temperature : ");
      Serial.print(t);
      Serial.print(" | Humidity : ");
      Serial.println(h);
    
    client.publish(temperature_topic, String(t).c_str(), true);   // Publish temperature on temperature_topic
    client.publish(humidity_topic, String(h).c_str(), true);      // and humidity
  }

}

// MQTT callback function
// D'après http://m2mio.tumblr.com/post/30048662088/a-simple-example-arduino-mqtt-m2mio
void callback(char* topic, byte* payload, unsigned int length) {

  int i = 0;
  if ( debug ) {
    Serial.println("Message recu =>  topic: " + String(topic));
    Serial.print(" | longueur: " + String(length,DEC));
  }
  // create character buffer with ending null terminator (string)
  for(i=0; i<length; i++) {
    message_buff[i] = payload[i];
  }
  message_buff[i] = '\0';

  String msgString = String(message_buff);
  if ( debug ) {
    Serial.println("Payload: " + msgString);
  }
}
