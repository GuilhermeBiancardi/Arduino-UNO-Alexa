#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Espalexa.h>

// Definições
#define pinoLaser 5
#define pinoVentilador 4
#define pinoAbajur 6

const char* SSID = "NOME_REDE";
const char* PASSWD = "SENHA_REDE";

Espalexa espalexa;

// Funções Bult-In
boolean connectWifi();
void controlerLaser(uint8_t brightness);
void controlerVentilador(uint8_t brightness);
void controlerAbajur(uint8_t brightness);

void setup() {

    pinMode(pinoLaser, OUTPUT);
    pinMode(pinoVentilador, OUTPUT);
    pinMode(pinoAbajur, OUTPUT);

    boolean wifiConnected = connectWifi();

    if (wifiConnected) {
        espalexa.addDevice("laser", controlerLaser);
        espalexa.addDevice("ventilador", controlerVentilador);
        espalexa.addDevice("abajur", controlerVentilador);
        espalexa.begin();
    } else {
        while (1) {
            Serial.println("Não foi possível conectar no WiFi.");
            delay(2500);
        }
    }
  
}

void loop() {
    espalexa.loop();
    delay(1);
}

// Verifica se a conexão com o WiFi foi bem sucedida
boolean connectWifi() {

    boolean state = true;
    int i = 0;

    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSWD);

    Serial.println("Conectando no WiFi...");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        if (i > 20) {
            state = false;
            break;
        }
        i++;
    }
    return state;

}

void controlerLaser(uint8_t brightness) {
    if (brightness == 255) {
        digitalWrite(pinoLaser, HIGH);
        Serial.println("Laser ON");
    } else {
        digitalWrite(pinoLaser, LOW);
        Serial.println("Laser OFF");
    }
}

void controlerVentilador(uint8_t brightness) {
    if (brightness == 255) {
        digitalWrite(pinoVentilador, HIGH);
        Serial.println("Ventilador ON");
    } else {
        digitalWrite(pinoVentilador, LOW);
        Serial.println("Ventilador OFF");
    }
}

void controlerAbajur(uint8_t brightness) {
    if (brightness == 0) {
        digitalWrite(pinoVentilador, LOW);
        Serial.println("Ventilador OFF");
    } else {
        digitalWrite(pinoVentilador, brightness);
        Serial.println("Ventilador ON");
    }
}