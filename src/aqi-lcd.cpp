
#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_ILI9341.h>
#include <ESP8266WiFi.h>

#include "config.h"
#include "interface.h"
#include "data-source/aqi-eco.h"

enum jsonType {
  AQI_ECO
};
#include "config.h"

#define TFT_CS D8
#define TFT_DC D1

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void setup() {
  Serial.begin(9600);
  Serial.println("AQI LCD is starting!");

  WiFi.begin(WIFI_SSD, WIFI_PASSWORD);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  tft.begin();
  tft.setRotation(0);
}

void loop(void) {
  displayModel model;

  jsonType type = JSON_TYPE;
  switch (type) {
    case AQI_ECO:
    getFromAqiEco(JSON_URL, &model);
    break;
  }
  drawScreen(&tft, &model);
  delay(1000 * 60);
}
