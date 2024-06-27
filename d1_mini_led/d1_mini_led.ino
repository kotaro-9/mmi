#include <ESP8266WiFi.h>
#include <PubSubCLient.h>

const char[] ssid = "BKO-IoT";
const char[] password = "Kingb3rdingMMI";
const char[] mqtt_server = "";
const char[] topic = "";

WiFiClient espClient;
MqttCLient cLient(espClient);

const int pinRed = D5;
const int pinGreen = D4;
const int pinBlue = D0; 


void setup() {
    Serial.begin(9600);

    // LED Setup
    pinMode(pinRed, OUTPUT);
    pinMode(pinGreen, OUTPUT);
    pinMode(pinBlue, OUTPUT);

    setup_wifi();
    client.setServer(mqtt_server, 1883)
    client.setCallback(update_led);
}


void loop() {
    if (!client.connected()) {
        reconnect_wifi();
    }
    client.loop();

    analogWrite(pinRed, 45);
    analogWrite(pinGreen, 114);
    analogWrite(pinBlue, 20);

    delay(3000);
}


void setup_wifi() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
}


void reconnect_wifi() {
    while (!client.connected()) {
        if (client.connect("ESP8266Client")) {
            client.subscribe(topic);
        } else {
            delay(5000);
        }
    }
}



// https://znil.net/index.php/ESP8266_Wemos_D1_Mini_mit_RGB-LED_Beispiel
// 1x (5V-1,95V)/20mA=152.5 Ohm
// 2x (5V-3,3V)/20mA=85 Ohm