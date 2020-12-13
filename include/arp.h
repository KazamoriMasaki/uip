/*
  Address resolution protocol implementation.
*/
#ifndef __ARP__
#define __ARP__
#include <stdint.h> /* for uint16_t */

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

struct arp_header
{
    uint16_t hw_type; /* hardware type. */
    uint16_t protocol_type; 
    uint16_t hw_size; /* hardware size. */
    uint8_t protocol_size; 
    uint16_t opcode;
    unsigned char data[];
}__attribute__((packed));

struct arp_ipv4
{
    unsigned char source_mac[6];
    uint32_t source_ip;
    unsigned char dest_mac[6];
    uint32_t dest_ip;
}__attribute__((packed));

#endif
