#ifndef __NETDEV__
#define __NETDEV__
#include <stdint.h>
/*
  Notes: 

  The socket buffer, or "SKB", is the most fundamental data structure in the Linux networking code. Every packet sent or received is handled using this data structure. 

  struct sk_buff {
	struct sk_buff		*next;
	struct sk_buff		*prev;

	struct sk_buff_head	*list;
	struct sock		*sk;
  }

  The first two members implement list handling.
  
  sk record the socket assosciated with this SKB. When a packet is sent or received for a socket, the memory assosciated with the packet must be charged to the socket for proper memory accounting. 
  
  Ref: http://vger.kernel.org/~davem/skb.html
*/
#include <linux/skbuff.h>

struct netdev {
    uint32_t addr;
    uint8_t addr_len;
    uint8_t hardware_addr[6];
    uint32_t mtu;
};

void netdev_init();

int netdev_transmit(struct sk_buff *skb, uint8_t *dest, uint16_t ethertype);

#endif
