#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>

#include "data-source/aqi-eco.h"

AqiEcoDataSource::AqiEcoDataSource(String url) {
  this->url = url;
}

boolean AqiEcoDataSource::readModel(JsonModel *model) {
  boolean result = false;
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  
  HTTPClient http;
  http.begin(*client, this->url);
  int httpCode = http.GET();
  Serial.printf("[HTTP] Response code: %d\n", httpCode);
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String body = http.getString();

      const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(8) + 2*JSON_OBJECT_SIZE(9);
      DynamicJsonDocument doc(capacity);
      deserializeJson(doc, body);

      JsonObject average_1h = doc["average_1h"];
      
      model->pm25 = average_1h["pm25"];
      model->pm10 = average_1h["pm10"];
      model->temp = average_1h["temperature"];
      model->humidity = average_1h["humidity"];
      model->pressure = average_1h["pressure"];
      result = true;
    }
  }
  http.end();
  return result;
}
