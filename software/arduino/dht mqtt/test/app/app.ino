#include <SoftwareSerial.h>
#include <WiFiEsp.h>
#include <SimpleTimer.h>
#include <PubSubClient.h>
#include <WifiUtil.h>

SoftwareSerial softSerial(2, 3);

WifiUtil wifi(2,3);

// const char SSID[] = "SK_WiFiGIGAD6C7";
// const char PASSWORD[] = "1710006158";
// const char mqtt_server[] = "192.168.35.178";

char SSID[] = "Campus7_Room3_2.4";
char PASSWORD[] = "12345678";
const char mqtt_server[] ="192.168.0.105";

WiFiEspClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
    payload[length] = NULL;
    char *message = payload;

    if(strcmp("1", message) == 0) {
        digitalWrite(13, HIGH);
    } else {
        digitalWrite(13, LOW);
    }

    Serial.print(topic);
    Serial.print(" : ");
    Serial.println(message);
}

void mqtt_init() {
    client.setServer(mqtt_server, 1883); //내 pc서버와 포트 번호
    client.setCallback(callback);
}

//MQTT 서버에 접속될 때까지 재접속 시도
void reconnect() {
    while(!client.connected()) {
        Serial.print("Attempting MQTT connection...");

        if(client.connect("ESP8266Client")) {
            //Subscriber로 등록
            client.subscribe("home/livingroom/led"); //여기서 아두이노가 Subscriber가 됨.
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());  //-2에러뜨는 경우 여기서
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void publish() {
    int state = !digitalRead(13);
    char message[10];
    sprintf(message, "%d", state);

    //토픽 발행
    client.publish("home/livingroom/led", message);
}

//2초 간격으로 publish
SimpleTimer timer;

void setup() {
    Serial.begin(115200);
    wifi.init(SSID, PASSWORD);
    mqtt_init();

    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    timer.setInterval(2000, publish);
}

void loop() {
    if(!client.connected()) {   //client연결이 안되어있음
        reconnect();            //재연결 시도
    }
    client.loop();
    timer.run();
}
