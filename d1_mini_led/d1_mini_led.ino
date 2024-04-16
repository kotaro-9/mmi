#include "ESP8266WiFi.h"

int pinRed = 5;
int pinGreen = 4;
int pinBlue = 0;

void setup() {
    Serial.begin(9600);

    // WiFi Setup
    WiFi.mode(WIFI_STA); // WiFi-Modus: Station; verbindet sich mit vorhandenen WiFi-Netzwerk
    WiFi.disconnect(); // Trenne Verbindung zu aktuellen WiFi-Netzwerk
    delay(100); // Verzoegerung um sicherzustellen, dass Trennung abgeschlossen ist

    Serial.println("WiFi Setup fertig");

    // LED Setup
    pinMode(pinRed, OUTPUT);
    pinMode(pinGreen, OUTPUT);
    pinMode(pinBlue, OUTPUT);
    Serial.println("Pins Setup fertig");
}

void loop() {
    Serial.println("WiFi Scan gestartet");

    int foundNetworks = WiFi.scanNetworks(); // Anzahl der gefundenen Netzwerke
    Serial.prinln("WiFi Scan abgeschlossen");

    if (foundNetworks == 0) {
        Serial.println("Keine WiFi-Netzwerke gefunden");
    } else {
        Serial.print(foundNetworks);

        // Ausgabe von SSID und RSSI von jedem Netzwerk
        for (int i = 0; i < foundNetworks; ++i) {
        Serial.print(++i);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.print(")");
        Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
        delay(10);
        }
    }
  
    Serial.print("");

    delay(5000); // Verzoegerung vor naechstem Scan
}





// https://znil.net/index.php/ESP8266_Wemos_D1_Mini_mit_RGB-LED_Beispiel