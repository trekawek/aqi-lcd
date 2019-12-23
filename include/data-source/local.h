#ifndef _LOCAL_DATA_SOURCE_H
#define _LOCAL_DATA_SOURCE_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <Print.h>
#include <StreamString.h>
#include <WiFiClientSecureBearSSL.h>

#include "mdns-resolver.h"
#include "model.h"
#include "data-source.h"

class LocalDataSource : public DataSource {
    public:
    LocalDataSource(String url, MDNSResolver *mdnsResolver);
    boolean readModel(JsonModel *model);

    private:
    boolean parseUrl(String url);
    static const String P10_VALUES[];
    static const String P25_VALUES[];
    static const String TEMP_VALUES[];
    static const String HUMIDITY_VALUES[];
    static const String PRESSURE_VALUES[];

    static boolean inArray(const String array[], String str);
    
    WiFiClient *client;
    DynamicJsonDocument *doc;
    MDNSResolver *mdnsResolver;

    String protocol;
    String host;
    char *hostArr;
    int port = -1;
    String path;
    boolean https = false;
    boolean local = false;
};

#endif