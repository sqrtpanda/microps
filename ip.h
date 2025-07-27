#ifndef IP_H
#define IP_H

#include <stdint.h>
#include <stddef.h>

#define IP_VERSION_IPV4 4

#define IP_HDR_SIZE_MIN 20
#define IP_HDR_SIZE_MAX 60

typedef uint32_t ip_addr_t;
#define IP_ADDR_STR_LEN 16

struct ip_endpoint {
    ip_addr_t addr;
    uint16_t port;
};

void ip_dump(const uint8_t *data, size_t len);
int ip_addr_pton(const char *p, ip_addr_t *n);
char *ip_addr_ntop(ip_addr_t n, char *p, size_t size);
int ip_init(void);

#endif