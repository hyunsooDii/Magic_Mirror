#include "WifiUtil.h"
#include <PubSubClient.h>
#include "DHT.h"          // Librairie des capteurs DHT
WifiUtil wifi(2, 3);
//
//const char SSID[] = "KT_GiGA_2G_Wave2_A8D7";
//const char PASSWORD[] = "zf3cbb5696";
const char SSID[] = "yonginDT";
const char PASSWORD[] = "12345678";
int relay_pin = 8;
int led_pin = 13;


//
//
//#define mqtt_server "172.30.1.34"
#define mqtt_server "192.168.0.110"
#define mqtt_user "localhost"      // if exist
#define mqtt_password ""  //idem

#define temperature_topic "sensor/temperature"  //Topic temperature
#define humidity_topic "sensor/humidity"        //Topic humidity

//Buffer to decode MQTT messages
char message_buff[100];

long lastMsg = 0;   
long lastRecu = 0;
bool debug = false;  //Display log message if True

WiFiEspClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);
  wifi.init(SSID, PASSWORD);     
//  setup_wifi();           //Connect to Wifi network
  client.setServer(mqtt_server, 1883);    // Configure MQTT connexion
  client.setCallback(callback);           // callback function to execute when a MQTT message   

  pinMode(relay_pin,OUTPUT);
  pinMode(led_pin,OUTPUT);  
  digitalWrite(led_pin,HIGH);
}

//Connexion au réseau WiFi
//void setup_wifi() {
//  delay(10);
//  Serial.println();
//  Serial.print("Connecting to ");
//  Serial.println(wifi_ssid);
//
//  WiFi.begin(wifi_ssid, wifi_password);
//
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//    Serial.print("\n");
//  }
//
//  Serial.println("");
//  Serial.println("WiFi OK ");
//  Serial.print("=> ESP8266 IP address: ");
//  Serial.print(WiFi.localIP());
//}

//Reconnexion
void reconnect() {

  while (!client.connected()) {
    Serial.print("Connecting to MQTT broker ...");
    if (client.connect("A2", mqtt_user, mqtt_password)) {
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
    
    // Read temperature in Celcius

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
