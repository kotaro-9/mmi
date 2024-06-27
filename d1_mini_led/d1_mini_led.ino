#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <PubSubCLient.h>

#define PORT 80

const char* ssid = "BKO-IoT";
const char* password = "Kingb3rdingMMI";
const char* mqtt_server = "192.168.178.30";
const char* mqttUsername = "LED"; 

WiFiClient espClient;

MqttCLient cLient(espClient);

ESP8266WebServer server(PORT)

const int pinRed = D5;
const int pinGreen = D4;
const int pinBlue = D0; 


void setup() {
    Serial.begin(9600);

    // WiFi Setup
    setup_wifi();
    client.setServer(mqtt_server, 1883)
    client.setCallback(update_led);

    // LED Setup
    pinMode(pinRed, OUTPUT);
    pinMode(pinGreen, OUTPUT);
    pinMode(pinBlue, OUTPUT);
}


void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        setup_wifi();
    }

    if (!client.connected()) {
        reconnect_mqtt();
    }

    client.loop();
    server.handleClient();

    delay(1000);
}


void setup_wifi() {
    delay(10);

    Serial.print("\n" + "Conecting to ");
    Serial.print("\n" + ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("WiFi connected");
    Serial.println("IP address: " + Wifi.localIP());
}


void reconnect_mqtt() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");

        if (client.connect("ESP8266Client")) {
            Serial.println("Connected");
            
            client.subscribe("led");
        } else {
            Serial.print("failed, rc=" + client.state());

            Serial.println("Trying again in 5 seconds.");
            delay(5000);
        }
    }
}


void test_led() {
    analogWrite(pinRed, 45);
    analogWrite(pinGreen, 114);
    analogWrite(pinBlue, 20);
}


// 1x (5V-1,95V)/20mA=152.5 Ohm
// 2x (5V-3,3V)/20mA=85 Ohm