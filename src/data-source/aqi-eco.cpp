#include <ESP8266HTTPClient.h>

#include "data-source/aqi-eco.h"

AqiEcoDataSource::AqiEcoDataSource(String url) {
  this->url = url;
  client = new BearSSL::WiFiClientSecure();
  client->setInsecure();
}

boolean AqiEcoDataSource::isReady() {
  return true;
}

boolean AqiEcoDataSource::readModel(JsonModel *model) {
  boolean result = false;
  Serial.print("[HTTP] Begin... (free heap: ");
  Serial.print(ESP.getFreeHeap());
  Serial.println(")");
  HTTPClient http;
  http.begin(*client, this->url);
  int httpCode = http.GET();
  Serial.printf("[HTTP] Response code: %d\r\n", httpCode);
  if (httpCode == HTTP_CODE_OK) {
    String body = http.getString();
    if (body.startsWith("{")) {
      Serial.println("[HTTP] Decoding result");
      deserializeJson(doc, body);
      JsonObject average_1h = doc["average_1h"];
      model->pm25 = average_1h["pm25"];
      model->pm10 = average_1h["pm10"];

      JsonObject last_data = doc["last_data"];
      model->temp = last_data["temperature"];
      model->humidity = last_data["humidity"];
      model->pressure = last_data["pressure"];
      result = true;
      Serial.println("[HTTP] Result decoded");
    }
  }
  http.end();
  Serial.println("[HTTP] Request finished");
  return result;
}
