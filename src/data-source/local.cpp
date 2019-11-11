#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

#include "data-source/local.h"

const String LocalDataSource::P10_VALUES[] = { "SDS_P1", "PMS_P1", "HPM_P1", "" };
const String LocalDataSource::P25_VALUES[] = { "SDS_P2", "PMS_P2", "HPM_P2", "" };
const String LocalDataSource::TEMP_VALUES[] = { "BME280_temperature", "BMP_temperature", "" };
const String LocalDataSource::HUMIDITY_VALUES[] = { "BME280_humidity", "" };
const String LocalDataSource::PRESSURE_VALUES[] = { "BME280_pressure", "BMP_pressure", "" };

LocalDataSource::LocalDataSource(String url) {
  this->url = url;
  const size_t capacity = JSON_ARRAY_SIZE(15) + 15*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 490;
  doc = new DynamicJsonDocument(capacity);
}

boolean LocalDataSource::readModel(JsonModel *model) {
  boolean result = false;
  WiFiClient client;
  HTTPClient http;
  Serial.println("[HTTP] Begin...");
  http.begin(client, url);
  int httpCode = 0;
  while (true) {
    httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
      break;
    }
    delay(1000);
  }
  Serial.printf("[HTTP] Response code: %d\r\n", httpCode);
  
  String body = http.getString();

  deserializeJson(*doc, body);

  JsonArray sensordatavalues = (*doc)["sensordatavalues"];
  for (auto value : sensordatavalues) {
    JsonObject o = value.as<JsonObject>();
    String n = o["value_type"];
    String v = o["value"];
    
    if (inArray(P10_VALUES, n)) {
      model->pm10 = v.toInt();
    } else if (inArray(P25_VALUES, n)) {
      model->pm25 = v.toInt();
    } else if (inArray(TEMP_VALUES, n)) {
      model->temp = v.toInt();
    } else if (inArray(HUMIDITY_VALUES, n)) {
      model->humidity = v.toInt();
    } else if (inArray(PRESSURE_VALUES, n)) {
      model->pressure = v.toInt() / 100;
    }
    result = true;
  }
  http.end();
  return result;
}

boolean LocalDataSource::inArray(const String array[], String str) {
  for (int i = 0; array[i].length() > 0; i++) {
    if (array[i] == str) {
      return true;
    }
  }
  return false;
}
