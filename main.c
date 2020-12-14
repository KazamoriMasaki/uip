#include "arp.h"
#include "ethernet.h"
#include "tuntap.h"

#define buffer_size (1 << 10)
char tun_buffer[buffer_size];

int main() {
    tun_init(); // init user space network program

    /* loop forever. */
    for(;;) {
	tun_read(tun_buffer, buffer_size);

	parse_ethernet();

	handle_packet();
    }

    return 0;
}
