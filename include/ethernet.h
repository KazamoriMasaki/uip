/*
  Definitions about Ethernet headers.
*/
#ifndef __ETHERNET__
#define __ETHERNET__
#include <linux/if_ether.h>
#include <linux/skbuff.h> /* for sk_buff */

struct ethernet_header
{
    uint8_t dest_mac[6];
    uint8_t source_mac[6];
    uint16_t type;
    uint8_t payload[]; // an empty array means a pointer
}__attribute__((packed));

struct ethernet_header* parse_ethernet_header(struct sk_buff *skb) {
    struct ethernet_header *hdr = (struct ethernet_header *)skb_head(skb);

    hdr -> type = ntohs(hdr -> type);

    return hdr;
}

#endif



