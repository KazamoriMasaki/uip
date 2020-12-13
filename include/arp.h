/*
  Address resolution protocol implementation.
*/
#ifndef __ARP__
#define __ARP__
#include <stdint.h> /* for uint16_t */
#include <arpa/inet.h> /* htonl(), htons(), ... */

#define ARP_ETHERNET
#define ARP_IPV4


struct arp_entry {
    struct list_head list; /* packet pending fro hardware address */
    struct netdev *dev; /* associated net interface */
    int32_t retry; /* arp request retrying times.*/
    int32_t ttl; /* entry timeout */
    uint32_t state; /* entry state */
    uint16_t pro; /*  */
    uint32_t ipaddr;
    uint8_t hwaddr[];
};

enum arp_op {
    REQUEST=1,
    REPLAY=2,

    /* RARP */
    RREQUEST=3,
    RREPLY=4,

    /* InARP */
    INREQUEST=8,
    INREPLY=9
};

struct arp_ipv4
{
    unsigned char source_mac[6];
    uint32_t source_ip;
    unsigned char dest_mac[6];
    uint32_t dest_ip;
}__attribute__((packed));

struct arp_header
{
    uint16_t hardware_type; /* hardware type. */
    uint16_t protocol_type; 
    uint16_t hardware_size; /* hardware size. */
    uint8_t protocol_size; 
    uint16_t opcode;
#if defined(ARP_ETHERNET) && defined(ARP_IP)
    struct arp_ipv4 ipv4;
#else
    unsigned char data[0];
#endif
}__attribute__((packed));

static inline void arp_hton(struct arp_header *arp) 
{
    arp -> hardware_type = htons(arp->hardware_type);
    arp -> protocol_type = htons(arp->protocol_type);
    arp -> opcode = htons(arp->opcode);
};

static inline void arp_noth(struct arp_header *arp) 
{
    arp -> hardware_type = ntohs(arp->hardware_type);
    arp -> protocol_type = ntohs(arp->protocol_type);
    arp -> opcode = ntohs(arp->opcode);
};

void arp_request(struct arp_entry *ae);
void arp_reply(struct netdev *dev, struct pkbuf *pkb);
void arp_recv(struct netdev *dev, struct pkbuf *pkb);



#endif
