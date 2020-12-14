/*
  Low lever virtual network driver, acts as the base of our network stack.
*/
#include <linux/if.h>
#include <linux/if_tun.h>

#include <stdio.h>  /* for printf() */
#include <stdlib.h> /* for exit() */
#include <string.h> /* for memset() */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> /* for open() */
#include <unistd.h> /* for close() */
#include <sys/ioctl.h>  /* for ioctl() */

int tun_read(char *buf, int len)
{
    return read(tun_fd, buf, len);
}

int tun_write(char *buf, int len)
{
    return write(tun_fd, buf, len);
}

int tun_free()
{
    close(tun_fd);
    free(dev);
}

int tun_alloc(char *dev)
{
    struct ifreq ifr;
    int tun_fd, err;

    if ( (tun_fd = open("/dev/net/tun", O_RDWR)) < 0) {
	fprintf(stderr,  "Can not open tun device.");
	exit(1);
    }

    memset(&ifr, 0, sizeof(ifr));  // clear ifr

    /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
     *        IFF_TAP   - TAP device
     *
     *        IFF_NO_PI - Do not provide packet information
     */
    ifr.ifr_flags = IFF_TUN | IFF_NO_PI; // avoid unnecessary packet information prepended to the Ethernet frame.

    if (* dev)
	strncpy(ifr.ifr_name, dev, IFNAMSIZ);

    if( (err = ioctl(tun_fd, TUNSETIFF, (void *) &ifr)) < 0 ) {
	close(tun_fd);
	return err;
    }

    strcpy(dev, ifr.ifr_name);
    return tun_fd;
}




