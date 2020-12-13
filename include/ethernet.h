/*
  Definitions about Ethernet headers.
*/
#ifndef __ETHERNET__
#define __ETHERNET__
#include <linux/if_ether.h>

struct ethernet_header
{
    uint8_t dest_mac[6];
    uint8_t source_mac[6];
    uint16_t type;
    uint8_t payload[]; // an empty array means a pointer
}__attribute__((packed));

#endif



