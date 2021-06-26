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

#define WIFI_NAME "DJOAMERSFOORT"
#define WIFI_PASS "l4anp4r7y"
#define SERVER_IP "100.64.0.180:8808"

// CODE

WiFiClient client;

Adafruit_BMP280 bmp;
Adafruit_CCS811 ccs;

Adafruit_NeoPixel led(1, PIN_LED, NEO_GRB + NEO_KHZ800);

// error function

void error() {
  while(true) {
    led.setPixelColor(0, led.Color(255, 0, 0));
    led.show();
    delay(500);
    led.setPixelColor(0, led.Color(0, 0, 0));
    led.show();
    delay(500); 
  }
}

// initialize connection

float ppm;
float temp;
float intensity;
String mac;

void setup() {
  bool success = true;
  
  led.begin();
  led.setBrightness(LED_INTENSITY);

  led.setPixelColor(0, led.Color(0, 0, 0));

  // enable sensors
  if(!ccs.begin(CCS_ADDR)) success = false;
  if(!bmp.begin(BMP_ADDR)) success = false;

  if(!success) error();

  // enable wifi
  WiFi.begin(WIFI_NAME, WIFI_PASS);
  
  while (WiFi.status() != WL_CONNECTED) {
      led.setPixelColor(0, led.Color(0, 0, 255));
      led.show();
      delay(500);
      led.setPixelColor(0, led.Color(0, 0, 0));
      led.show();
      delay(500); 
  }

  mac = WiFi.macAddress();
}

// send data to server

void sendUpdate() {
  HTTPClient http;
  String query = "?id=" + mac + "&ppm=" + ppm + "&temp=" + temp;
  http.begin(client, "http://" SERVER_IP "/update" + query);
  int code = http.GET();

  if(code != HTTP_CODE_OK) error();
  http.end();
}

void updateLed() {
  intensity = ppm / CO2_DANGER * 255;

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
      sendUpdate();
    }
  }
  
  delay(10000);
}
