#include <ESP8266HTTPClient.h>

#include "data-source/aqi-eco.h"

AqiEcoDataSource::AqiEcoDataSource(String url) {
  this->url = url;
  client = new BearSSL::WiFiClientSecure();
  client->setInsecure();

  const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(8) + 2*JSON_OBJECT_SIZE(9);
  doc = new DynamicJsonDocument(capacity);
}

boolean AqiEcoDataSource::readModel(JsonModel *model) {
  boolean result = false;
  HTTPClient http;
  http.begin(*client, this->url);
  int httpCode = http.GET();
  Serial.printf("[HTTP] Response code: %d\r\n", httpCode);
  if (httpCode == HTTP_CODE_OK) {
    String body = http.getString();
    if (body.startsWith("{")) {
      Serial.println("[HTTP] Decoding result");
      deserializeJson(*doc, body);
      JsonObject average_1h = (*doc)["average_1h"];
      model->pm25 = average_1h["pm25"];
      model->pm10 = average_1h["pm10"];
      model->temp = average_1h["temperature"];
      model->humidity = average_1h["humidity"];
      model->pressure = average_1h["pressure"];
      result = true;
      Serial.println("[HTTP] Result decoded");
    }
  }
  http.end();
  Serial.println("[HTTP] Request finished");
  return result;
}
