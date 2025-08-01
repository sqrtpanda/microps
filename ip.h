#ifndef IP_H
#define IP_H

#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>

#include "net.h"

#define IP_VERSION_IPV4 4

#define IP_HDR_SIZE_MIN 20
#define IP_HDR_SIZE_MAX 60

#define IP_TOTAL_SIZE_MAX UINT16_MAX

typedef uint32_t ip_addr_t;
#define IP_ADDR_STR_LEN 16

#define IP_PROTOCOL_ICMP 1
#define IP_PROTOCOL_TCP 6
#define IP_PROTOCOL_UDP 17

struct ip_endpoint
{
    ip_addr_t addr;
    uint16_t port;
};

struct ip_iface
{
    struct net_iface iface;
    struct ip_iface *next;
    ip_addr_t unicast;
    ip_addr_t netmask;
    ip_addr_t broadcast;
};

void ip_dump(const uint8_t *data, size_t len);
int ip_addr_pton(const char *p, ip_addr_t *n);
char *ip_addr_ntop(ip_addr_t n, char *p, size_t size);
ssize_t ip_output(uint8_t protocol, const uint8_t *data, size_t len, ip_addr_t src, ip_addr_t dst);
struct ip_iface *ip_iface_alloc(const char *unicast, const char *netmask);
int ip_iface_register(struct net_device *dev, struct ip_iface *iface);
int ip_protocol_register(uint8_t type, void (*handler)(const uint8_t *data, size_t len, ip_addr_t src, ip_addr_t dst, struct ip_iface *iface));
struct ip_iface *ip_iface_select(ip_addr_t addr);
int ip_init(void);

#endif