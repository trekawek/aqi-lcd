
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans9pt7b.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>

typedef struct
{
  const uint16_t *data;
  uint16_t width;
  uint16_t height;
  uint8_t  dataSize;
} tImage;

#include "bitmaps/icon-humidity.h"
#include "bitmaps/icon-pm10.h"
#include "bitmaps/icon-pm25.h"
#include "bitmaps/icon-pressure.h"
#include "bitmaps/icon-temp.h"
//#include "bitmaps/levels.h"

#define TFT_CS D8
#define TFT_DC D1

#define BLACK 0x0000
#define WHITE 0xFFFF

#define INDICATOR_RADIUS 4
#define INDICATOR_LENGTH 40
#define INDICATOR_COLOR 0x0339

static const int PM25_LEVELS[] = {0, 15, 30, 55, 110, 32768};
static const int PM10_LEVELS[] = {0, 25, 50, 90, 180, 32768};
static const int PM25_MAX = 25;
static const int PM10_MAX = 50;

typedef struct {
  uint16_t pm25;
  uint16_t pm10;
  uint16_t temp;
  uint16_t humidity;
  uint16_t pressure;
} displayModel;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

enum jsonType {
  AQI_ECO
};
#include "config.h"

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
  drawScreen(&model);
  delay(1000 * 60);
}

void getFromAqiEco(String url, displayModel *model) {
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  
  HTTPClient http;
  Serial.print("[HTTP] begin...\n");
  http.begin(*client, url);
  int httpCode = http.GET();
  Serial.printf("[HTTP] Response code: %d\n", httpCode);
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String body = http.getString();

      const size_t capacity = JSON_OBJECT_SIZE(3) + 3*JSON_OBJECT_SIZE(8) + 340;
      DynamicJsonDocument doc(capacity);
      deserializeJson(doc, body);

      JsonObject average_1h = doc["average_1h"];
      
      model->pm25 = average_1h["pm25"];
      model->pm10 = average_1h["pm10"];
      model->temp = average_1h["temperature"];
      model->humidity = average_1h["humidity"];
      model->pressure = average_1h["pressure"];
    }
  }
  http.end();
}

int getIndex(const displayModel *model) {
  int pm25Index = getIndex(model->pm25, PM25_LEVELS);
  int pm10Index = getIndex(model->pm10, PM10_LEVELS);
  return max(pm25Index, pm10Index);
}

int getIndex(int v, const int levels[]) {
  for (int i = 0; ; i++) {
    if (levels[i] > v) {
      return i - 1;
    }
  }
}

void drawScreen(const displayModel *model) {
  int pm25rel = model->pm25 * 100 / PM25_MAX;
  int pm10rel = model->pm10 * 100 / PM10_MAX;
  int index = getIndex(model);
  
  tft.fillScreen(0);

  drawLevels(120, 75);
  
  float percent[] = {0.1, 0.3, 0.5, 0.7, 0.9};
  drawIndicator(percent[index], 120, 75);
  
  tft.setTextColor(WHITE);
  tft.setTextSize(1);

  // pm 2.5
  tft.setCursor(55, 100);
  tft.setFont(&FreeSans12pt7b);
  tft.print(model->pm25);
  tft.setFont(&FreeSans9pt7b);
  tft.print("ug/m3");

  tft.setFont(&FreeSans12pt7b);
  tft.setCursor(145, 105);
  tft.print(pm25rel);
  tft.print("%");

  // pm 10
  tft.setCursor(55, 150);
  tft.setFont(&FreeSans12pt7b);
  tft.print(model->pm10);
  tft.setFont(&FreeSans9pt7b);
  tft.print("ug/m3");

  tft.setFont(&FreeSans12pt7b);
  tft.setCursor(145, 150);
  tft.print(pm10rel);
  tft.print("%");

  // temp
  tft.setCursor(90, 200);
  tft.print(model->temp);
  tft.print("'C");

  // humidity
  tft.setCursor(90, 250);
  tft.print(model->humidity);
  tft.print("%");

  // pressure
  tft.setCursor(90, 300);
  tft.print(model->pressure);
  tft.print(" hPa");

  drawBitmap(6, 79, &iconpm25);
  drawBitmap(5, 129, &iconpm10);
  drawBitmap(7, 174, &icontemp);
  drawBitmap(3, 227, &iconhumidity);
  drawBitmap(3, 275, &iconpressure);
}

void drawBitmap(uint16_t x, uint16_t y, const tImage *image) {
  uint16_t pix = 0;
  uint16_t x0, y0;
  const uint16_t *pdata = image->data;
  for (y0 = 0; y0 < image->height; y0++) {
    for (x0 = 0; x0 < image->width; x0++) {
      tft.drawPixel(x + x0, y + y0, *pdata++);
    }
  }
}

void drawLevels(uint16_t x, uint16_t y) {
  tft.fillCircle(x, y, 70, INDICATOR_COLOR);
  
  uint16_t colors[] = {0x2d24, 0xa644, 0xff66, 0xfd65, 0xf963};
  
  uint16_t x2 = x - 60;
  uint16_t y2 = y;

  for (float i = 0; i < 5; i += 0.1) {
    float angle = PI * i / 5;
    
    uint16_t x3 = sin(PI + HALF_PI - angle) * 60 + x;
    uint16_t y3 = cos(PI + HALF_PI - angle) * 60 + y;

    tft.fillTriangle(x, y, x2, y2, x3, y3, colors[(int)i]);

    x2 = x3;
    y2 = y3;
  }
  
  tft.fillCircle(x, y, 20, BLACK);
  tft.fillRect(x - 70, y, 150, 70, BLACK);
}

void drawIndicator(float percent, uint16_t x, uint16_t y) {
  float angle = percent * PI;
  tft.fillCircle(x, y, INDICATOR_RADIUS, INDICATOR_COLOR);

  uint16_t x1 = sin(-angle) * (INDICATOR_RADIUS - 2) + x;
  uint16_t y1 = cos(-angle) * (INDICATOR_RADIUS - 2) + y;

  uint16_t x2 = sin(-angle + PI) * (INDICATOR_RADIUS - 2) + x;
  uint16_t y2 = cos(-angle + PI) * (INDICATOR_RADIUS - 2) + y;

  uint16_t x3 = sin(PI + HALF_PI - angle) * INDICATOR_LENGTH + x;
  uint16_t y3 = cos(PI + HALF_PI - angle) * INDICATOR_LENGTH + y;

  tft.fillTriangle(x1, y1, x2, y2, x3, y3, INDICATOR_COLOR);
}
