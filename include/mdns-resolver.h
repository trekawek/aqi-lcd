#ifndef _MDNS_RESOLVER_H
#define _MDNS_RESOLVER_H

#include <ESP8266WiFi.h>
#include <mDNSResolver.h>
#include <WiFiUdp.h>

using namespace mDNSResolver;

class MDNSResolver {
    public:
    MDNSResolver();
    void setup(const char* addressToResolve);
    void loop();

    bool isResolved();
    char *getResolvedIp();

    private:
    void doResolve();

    WiFiUDP *udp;
    Resolver *resolver;

    char query[256];
    char response[256];
    long lastUpdate;
    bool initialized = false;
    bool resolved = false;
};

#endif