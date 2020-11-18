#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>


//------------------------------------------
//SETUP LED
long time_led;
#define LED_DELAY 1000
#define LED_PIN 2


//------------------------------------------
//SETUP RELAY
#define RELAY0_PIN D2
#define RELAY1_PIN D1
#define RELAY2_PIN D5
#define RELAY3_PIN D6

//------------------------------------------
//SETUP BUTTON
#define BUTTON_PIN D3
#define BUTTON_DELAY 300

long t_button;

//------------------------------------------
//WIFI i server HTTP
ESP8266WebServer server(80);
#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define HOST_NAME "onoff"


bool button_last;
long t_now;

void setup() {
  //Setup pin mode
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT); //Initialize onboard LED as output
  pinMode(RELAY0_PIN, OUTPUT);
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(RELAY3_PIN, OUTPUT);
  SW_all_off(); //Turn off all relays
  button_last = HIGH;

  //Setup UART
  Serial.begin(115200);
  Serial.println("");
  Serial.println("START");

  //Setup WIFI 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.hostname( HOST_NAME );
  Serial.print("Connecting to WIFI");

  //Wait for WIFI connection
  while( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println( WIFI_SSID );
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //Setup HTTP server
  server.on("/", handleRoot);
  server.on("/sw", handleSW);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
  
}
 
void loop() {
  t_now = millis();
  
  server.handleClient();

  //Blinking an LED
  if( t_now - time_led > LED_DELAY ){
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    time_led = t_now;
  }

  //Check button
  bool b = digitalRead( BUTTON_PIN );
  if( b != button_last && t_now - t_button > BUTTON_DELAY ){
    if( b==HIGH && button_last==LOW ){
      SW(0, digitalRead( RELAY0_PIN ));
      Serial.println("BUTTON");
    }

    t_button = t_now;
    button_last = b;
  }
}

void SW_all_on(){
  digitalWrite(RELAY0_PIN, LOW);
  digitalWrite(RELAY1_PIN, LOW);
  digitalWrite(RELAY2_PIN, LOW);
  digitalWrite(RELAY3_PIN, LOW);
}

void SW_all_off(){
  digitalWrite(RELAY0_PIN, HIGH);
  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);
  digitalWrite(RELAY3_PIN, HIGH);
}

void SW(byte num, bool sw){
  switch( num ){
    case 0: digitalWrite(RELAY0_PIN, !sw); break;
    case 1: digitalWrite(RELAY1_PIN, !sw); break;
    case 2: digitalWrite(RELAY2_PIN, !sw); break;
    case 3: digitalWrite(RELAY3_PIN, !sw); break;
  }
}

void handleRoot(){
  String html = "<!DOCTYPE html>\r\n";
  html += "<html>\r\n";
  html += "<head>\r\n";
  html += "<meta charset='UTF-8'>\r\n";
  html += "<title>ESP8266</title>\r\n";
  html += "<body>\r\n";

  html += "ESP8266 - ";
  html += HOST_NAME;
  html += "\r\n";

  if( !digitalRead(RELAY0_PIN) ){
    html += "<a href='sw?sw=off' style='display: inline-block; width: 100px; background-color: red; text-align: center;'>OFF</a>\r\n";
  }else{
    html += "<a href='sw?sw=on' style='display: inline-block; width: 100px; background-color: green; text-align: center;'>ON</a>\r\n";
  }
  
  //html += "<br>\r\n";
  //html += "<a href='sw?sw=on'>LED On</a>\r\n";
  //html += "<a href='sw?sw=off'>LED Off</a>\r\n";
  
  html += "</body>\r\n";
  html += "</html>\r\n";

  
  server.send(200, "text/html", html);
}

void handleSW(){
  if (server.arg("sw")== "on"){
    SW(0, HIGH);
  }else{
    SW(0, LOW);
  }

  String ip = WiFi.localIP().toString();
  server.sendHeader("Location", String("http://") + ip, true);
  server.send ( 302, "text/plain", "");
  server.client().stop();
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
