#include "mdns-resolver.h"

MDNSResolver::MDNSResolver() {
    udp = new WiFiUDP();
    resolver = new Resolver(*udp);
}

void MDNSResolver::setup(const char* addressToResolve) {
    resolver->setLocalIP(WiFi.localIP());
    strncpy(query, addressToResolve, 256);
    initialized = true;
}

void MDNSResolver::loop() {
    if (!initialized) {
        return;
    }
    resolver->loop();
    if (lastUpdate == 0 || millis() - lastUpdate > 30 * 60 * 1000) {
        doResolve();
    }    
}

void MDNSResolver::doResolve() {
    Serial.printf("[mdns] Resolving %s\r\n", query);
    IPAddress result = resolver->search(query);
    if (result == INADDR_NONE) {
        Serial.println("[mdns] Can't resolve");
        return;
    }
    result.toString().toCharArray(response, 256, 0);
    Serial.printf("[mdns] Response %s\r\n", response);
    resolved = true;
    lastUpdate = millis();
}

boolean MDNSResolver::isResolved() {
    return resolved;
}

char* MDNSResolver::getResolvedIp() {
    return response;
}