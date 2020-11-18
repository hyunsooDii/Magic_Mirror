#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include <WiFiEsp.h>
#include <PubSubClient.h>
#include <SimpleTimer.h>
#include <WifiUtil.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define NUMPIXELS 10
SoftwareSerial softSerial(2, 3);           // RX, TX
const char ssid[] = "yonginDT";               // 네트워크 SSID
const char password[] = "12345678";       // 비밀번호
const char mqtt_server[] = "192.168.137.185"; // 서버 주소

// MQTT용 WiFi 클라이언트 객체 초기화
WifiUtil wifi(2, 3);
WiFiEspClient espClient;
PubSubClient client(espClient);



int pSensor = A0;
int mirror_ledPin = 6;
int heater_ledPin = 13;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, mirror_ledPin, NEO_GRB + NEO_KHZ800);

void callback(char *topic, byte *payload, unsigned int length) {
    payload[length] = NULL;
    char *message = payload;

    if (strcmp("1", message) == 0) {
        digitalWrite(heater_ledPin, HIGH);
        for(int i=0; i<NUMPIXELS; i++){
            pixels.setPixelColor(i,255,255,255);
        }
        pixels.show();
    } else {
        digitalWrite(heater_ledPin, LOW);
        for(int i=0; i<NUMPIXELS; i++){
            pixels.setPixelColor(i,0,0,0); 
        }
        pixels.show();
    }

    Serial.print(topic);
    Serial.print(" : ");
    Serial.println(message);
}

void mqtt_init() {
    client.setServer(mqtt_server, 1883);
    // subscriber인경우 메시지 수신시 호출할 콜백 함수 등록
    client.setCallback(callback);
}

// MQTT 서버에 접속될 때까지 재접속 시도
void reconnect() {

    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        
        if (client.connect("ESP8266Client")) {
            Serial.println("connected");
            // subscriber로 등록
            client.subscribe("iot/home/#",1);  // 구독 신청
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void publish() {
    char message[10];
    int readVal = analogRead(pSensor);
    dtostrf(readVal, 5, 2, message);
    // 토픽 발행
    // client.publish("iot/home/Illuminance", message);

}

// 2초 간격으로 publish
SimpleTimer timer;



void setup() {
    Serial.begin(9600);
    #if defined (__AVR_ATtiny85__)
        if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
    #endif

    wifi.init(ssid, password);
    mqtt_init();
    pinMode(heater_ledPin, OUTPUT);
    digitalWrite(heater_ledPin, LOW);


    // timer.setInterval(2000, publish);
    pixels.begin();
}

void loop() {
     if (!client.connected()) {  // MQTT가 연결 X
        reconnect();
    }
    client.loop();
    timer.run();

    int readVal = analogRead(pSensor);
    // Serial.print("Read Value = ");
    // Serial.println(readVal);

    // if(readVal > 989) { // 어두워지면 LED 켜기
    //     for(int i=0; i<NUMPIXELS; i++){
    //         pixels.setPixelColor(i,255,255,255);
    //     }

    //     pixels.show();
    // } else {
    //     for(int i=0; i<NUMPIXELS; i++){
    //         pixels.setPixelColor(i,0,0,0); 
    //     }

    //     pixels.show();
    // }
    // delay(200);
}