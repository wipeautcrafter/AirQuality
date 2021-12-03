#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "Adafruit_CCS811.h"
#include "Adafruit_BMP280.h"
#include "Adafruit_NeoPixel.h"

// DEFINE CO2 DANGER LEVELS

#define CO2_DANGER 1500
#define LED_INTENSITY 50

#define BMP_ADDR 0x76
#define CCS_ADDR 0x5A
#define PIN_LED  D4

// DEFINE WIFI SETTINGS

#define WIFI_NAME "Farel-gasten"
#define WIFI_PASS "dPP924fR"
//#define WIFI_NAME "DJOAMERSFOORT"
//#define WIFI_PASS "l4anp4r7y"

#define SERVER_IP "co2.wipeaut.nl"

#define SLEEP_TIME 2 * 60 * 1000 // 2 minutes

// ERROR CODES

#define ERROR_PIN LED_BUILTIN
#define ERROR_TRIES 6

#define ERROR_DELAY 5000
#define ERROR_BLINK 500
#define ERROR_SEND 2
#define ERROR_SENSOR 3

// CODE

WiFiClient client;

Adafruit_BMP280 bmp;
Adafruit_CCS811 ccs;

Adafruit_NeoPixel led(1, PIN_LED, NEO_GRB + NEO_KHZ800);

// initialize connection

int tries = 0;

float ppm;
float temp;
float intensity;
String mac;

unsigned long interval;

// status code

void errorCode(int n) {
  for(int i = 0; i < n; i++) {
    digitalWrite(ERROR_PIN, HIGH);
    delay(ERROR_BLINK);
    digitalWrite(ERROR_PIN, LOW);
    delay(ERROR_BLINK);
  }
}

void setup() {
  bool success = true;
  
  // set pins to output
  pinMode(PIN_LED, OUTPUT);
  pinMode(ERROR_PIN, OUTPUT);
  digitalWrite(ERROR_PIN, LOW);

  // setup led
  led.begin();
  led.setBrightness(LED_INTENSITY);

  // update leds
  led.clear();
  led.show();

  // enable sensors
  if(!ccs.begin(CCS_ADDR)) success = false;
  if(!bmp.begin(BMP_ADDR)) success = false;
  
  if(!success) {
    while(true) {
      errorCode(ERROR_SENSOR);
      delay(ERROR_DELAY);
    }
  }

  // enable wifi
  WiFi.begin(WIFI_NAME, WIFI_PASS);
  
  while (WiFi.status() != WL_CONNECTED) {
    errorCode(1);
  }
  
  // log mac in console for setup
  mac = WiFi.macAddress();
}

// send data to server

int sendUpdate() {
  HTTPClient http;
  String query = "?id=" + mac + "&ppm=" + ppm + "&temp=" + temp;
  http.begin(client, "http://" SERVER_IP "/update" + query);
  int code = http.GET();
  http.end();

  return code;
}

void updateLed() {
  intensity = min((ppm / CO2_DANGER) * 255, (float) 255);

  led.setPixelColor(0, led.Color(intensity, 255 - intensity, 0));
  led.show();
}

// update loop

int i = 0;

void loop() {
  if(ccs.available()) {
    if(!ccs.readData()) {
      ppm = ccs.geteCO2();
      temp = bmp.readTemperature();

      updateLed();

      if(abs(millis() - interval) > 10000) {
        // try sending the sensor value
        switch(sendUpdate()) {
          case HTTP_CODE_OK:
            tries = 0;
            break;
          case 503:
            led.setPixelColor(0, led.Color(0, 0, 10));
            led.show();
            
            delay(SLEEP_TIME);
            break;
          case 426:
            ESP.restart();
            break;
          default:
            errorCode(ERROR_SEND);

            tries++;
            if(tries >= ERROR_TRIES) ESP.restart();
            
            break;
        }

        interval = millis();
      }
    }
  }
}
