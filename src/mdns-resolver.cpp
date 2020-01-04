#include "mdns-resolver.h"

MDNSResolver::MDNSResolver() {
    buffer = new byte[MAX_MDNS_PACKET_SIZE];
}

void MDNSResolver::setup(const char* addressToResolve) {
    mdns = new mdns::MDns(NULL, NULL, ([this](const mdns::Answer* answer){
        if (strncmp(query.qname_buffer, answer->name_buffer, MAX_MDNS_NAME_LEN) == 0) {
            strncpy(response, answer->rdata_buffer, MAX_MDNS_NAME_LEN);
            Serial.print("[mdns] ");
            Serial.print(query.qname_buffer);
            Serial.print(" resolved to ");
            Serial.println(response);
            resolved = true;
        }
    }), buffer, MAX_MDNS_PACKET_SIZE);

    strncpy(query.qname_buffer, addressToResolve, MAX_MDNS_NAME_LEN);
    query.qtype = MDNS_TYPE_A;
    query.qclass = 1;
    query.unicast_response = 0;
}

void MDNSResolver::loop() {
    if (mdns == NULL) {
        return;
    }
    if ((lastUpdate == 0 || millis() - lastUpdate > 30 * 60 * 1000)) {
        doResolve();
        resolved = false;
        lastUpdate = millis();
    }
    if (!resolved) {
        mdns->loop();
    }
}

void MDNSResolver::doResolve() {
    mdns->Clear();
    mdns->AddQuery(query);
    mdns->Send();
    Serial.println("[mdns] Query sent");
}

boolean MDNSResolver::isResolved() {
    return resolved;
}

char* MDNSResolver::getResolvedIp() {
    return response;
}