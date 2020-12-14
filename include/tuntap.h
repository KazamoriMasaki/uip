/*
  TUNTAP -- Linux user space network interface.
*/
#ifndef __TUNTAP__
#define __TUNTAP__

static int tun_fd; /* tuntap file descriptor */
static char *dev;

int tun_alloc(char *dev);

void tun_init();

int tun_read(char *buf, int len);
int tun_write(char *buf, int len);
#endif
