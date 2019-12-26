#ifndef _MDNS_RESOLVER_H
#define _MDNS_RESOLVER_H

#define MAX_MDNS_PACKET_SIZE 2048

#include <mdns.h>

using namespace mdns;

class MDNSResolver {
    public:
    MDNSResolver();
    void setup(const char* addressToResolve);
    void loop();

    boolean isResolved();
    char *getResolvedIp();

    private:
    void doResolve();

    MDns *mdns;
    byte *buffer;
    long lastUpdate;

    struct Query query;
    char response[MAX_MDNS_NAME_LEN];

    boolean isQueryInitialized = false;
    boolean resolved = false;
};

#endif