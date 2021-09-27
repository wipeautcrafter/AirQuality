#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "Adafruit_CCS811.h"
#include "Adafruit_BMP280.h"
#include "Adafruit_NeoPixel.h"

// DEFINE CO2 DANGER LEVELS

#define CO2_DANGER 1500
#define LED_INTENSITY 100

#define BMP_ADDR 0x76
#define CCS_ADDR 0x5A
#define PIN_LED  D4

// DEFINE WIFI SETTINGS

#define WIFI_NAME "Farel-gasten"
#define WIFI_PASS "dPP924fR"
#define SERVER_IP "co2.wipeaut.nl"

// CODE

WiFiClient client;

Adafruit_BMP280 bmp;
Adafruit_CCS811 ccs;

Adafruit_NeoPixel led(1, PIN_LED, NEO_GRB + NEO_KHZ800);

// error function

void flash(int r, int g, int b, int d) {
  led.setPixelColor(0, led.Color(r, g, b));
  led.show();
  delay(d);
  led.setPixelColor(0, led.Color(0, 0, 0));
  led.show();
  delay(d);
}

// initialize connection

float ppm;
float temp;
float intensity;
String mac;

unsigned long interval;

void setup() {
  Serial.begin(9600);
  bool success = true;
  
  led.begin();
  led.setBrightness(LED_INTENSITY);

  led.setPixelColor(0, led.Color(0, 0, 0));

  // enable sensors
  if(!ccs.begin(CCS_ADDR)) success = false;
  if(!bmp.begin(BMP_ADDR)) success = false;

  if(!success) {
    while(true) flash(255, 0, 0, 500);
  }

  // enable wifi
  WiFi.begin(WIFI_NAME, WIFI_PASS);
  
  while (WiFi.status() != WL_CONNECTED) {
      flash(0, 0, 255, 500);
  }
  
  // log mac in console for setup
  mac = WiFi.macAddress();
  Serial.println(mac);
  Serial.end();
}

// send data to server

bool sendUpdate() {
  HTTPClient http;
  String query = "?id=" + mac + "&ppm=" + ppm + "&temp=" + temp;
  http.begin(client, "http://" SERVER_IP "/update" + query);
  int code = http.GET();
  http.end();

  return code == HTTP_CODE_OK;
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

      if(abs(millis() - interval) > 10000) {
        // try sending and blink on error
        while(!sendUpdate()) {
          flash(255, 0, 0, 250);
        }

        interval = millis();
      }

      updateLed();
    }
  }
}
