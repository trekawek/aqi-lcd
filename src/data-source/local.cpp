#include "data-source/local.h"

const String LocalDataSource::P10_VALUES[] = { "SDS_P1", "PMS_P1", "HPM_P1", "" };
const String LocalDataSource::P25_VALUES[] = { "SDS_P2", "PMS_P2", "HPM_P2", "" };
const String LocalDataSource::TEMP_VALUES[] = { "BME280_temperature", "BMP_temperature", "" };
const String LocalDataSource::HUMIDITY_VALUES[] = { "BME280_humidity", "" };
const String LocalDataSource::PRESSURE_VALUES[] = { "BME280_pressure", "BMP_pressure", "" };

LocalDataSource::LocalDataSource(String url, MDNSResolver *mdnsResolver) {
  this->url = url;
  this->mdnsResolver = mdnsResolver;
  this->client = new WiFiClient();

  parseUrl(url);
  if (local) {
    mdnsResolver->setup(hostArr);
  }
}

boolean LocalDataSource::isReady() {
  if (local) {
    return mdnsResolver->isResolved();
  } else {
    return true;
  }
}

boolean LocalDataSource::readModel(JsonModel *model) {
  boolean result = false;
  HTTPClient http;
  Serial.println("[HTTP] Begin...");
  if (this->path.length() == 0) {
    http.begin(*client, this->url);
  } else {
    if (local) {
      if (mdnsResolver->isResolved()) {
        http.begin(*client, mdnsResolver->getResolvedIp(), port, path, https);
      } else {
        Serial.print("[HTTP] Can't resolve ");
        Serial.println(hostArr);
        return false;
      }
    } else {
      http.begin(*client, host, port, path, https);
    }
  }
  int httpCode = http.GET();
  Serial.printf("[HTTP] Response code: %d\r\n", httpCode);
  if (httpCode == HTTP_CODE_OK) {
    String body = http.getString();
    if (body.startsWith("{")) {
      Serial.println("[HTTP] Decoding result");
      deserializeJson(doc, body);
      JsonArray sensordatavalues = doc["sensordatavalues"];
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
      }
      result = true;
      Serial.println("[HTTP] Result decoded");
    }
  }
  http.end();
  Serial.println("[HTTP] Request finished");
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

boolean LocalDataSource::parseUrl(String url) {
    int index = url.indexOf(':');
    if (index < 0) {
        return false;
    }

    protocol = url.substring(0, index);
    url.remove(0, (index + 3));

    if (protocol == "http") {
        port = 80;
        https = false;
    } else if (protocol == "https") {
        port = 443;
        https = true;
    } else {
        return false;
    }

    index = url.indexOf('/');
    host = url.substring(0, index);
    url.remove(0, index);

    index = host.indexOf(':');
    if (index >= 0) {
        port = host.substring(index + 1).toInt();
        host.remove(0, (index + 1));
    }
    local = host.endsWith(".local");
    if (local) {
      hostArr = (char*) calloc(host.length() + 1, sizeof(char));
      host.toCharArray(hostArr, host.length() + 1, 0);
    }
    path = url;
    return true;
}
