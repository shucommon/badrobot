/* read /proc/net/dev repeatedly, and complain about huge deltas */
/* chuck@knight.com */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/select.h>
#include <signal.h>
#include <netinet/tcp.h>
#include <sys/time.h>

#define MAX_IFACE_LEN IFNAMSIZ
#define MINIMUM(a,b)      ((a) < (b) ? (a) : (b))
#define MAXDEV 32

/* exit after this many errors */
#define ERROR_LIMIT 10e5

/* complain about a delta above this */
#define DELTA_LIMIT ((long long)10e10)


struct stats_net_dev {
   struct timeval time;
   char *orig_buf;
   long long rx_packets;
   long long tx_packets;
   long long rx_bytes;
   long long tx_bytes;
   long long rx_compressed;
   long long tx_compressed;
   long long multicast;
   long long collisions;
   long long rx_errors;
   long long tx_errors;
   long long rx_dropped;
   long long tx_dropped;
   long long rx_fifo_errors;
   long long tx_fifo_errors;
   long long rx_frame_errors;
   long long tx_carrier_errors;
   char interface[32];
};


int max_dev = 0;

/*
 ***************************************************************************
 * Read stats from /proc/net/dev
 ***************************************************************************
 */
struct stats_net_dev *read_net_dev_stat(void)
{
   struct stats_net_dev *st_net_dev_i, *st_net_dev;
   char *line;
   char iface[32];
   unsigned int dev = 0;
   int pos;
   char proc_net_dev_buf[40960];
   int buflen, fd;
   char *p1, *p2;
   char *orig_buf;
   
   st_net_dev=malloc(sizeof(struct stats_net_dev) * MAXDEV);
   memset(st_net_dev, 0, sizeof(struct stats_net_dev) * MAXDEV);
   orig_buf=malloc(sizeof(proc_net_dev_buf));
   memset(orig_buf, 0, sizeof(proc_net_dev_buf));

   if ((fd = open("/proc/net/dev", O_RDONLY)) >= 0) {
      buflen = read(fd, proc_net_dev_buf, sizeof(proc_net_dev_buf)-1);
      close(fd);
      if(buflen<=0) {
	 printf("read /proc/net/dev returned 0\n");
	 exit(1);
      }
      memcpy(orig_buf, proc_net_dev_buf, buflen);
   } else {
      perror("open");
      exit(1);
   }

   proc_net_dev_buf[buflen] = 0;
   p1 = proc_net_dev_buf;

   while (p1 != NULL && dev < MAXDEV) {
      p2=strchr(p1, '\n');
      if(p2) { // newline found, make it a null and copy the line in place
	  *p2='\0'; //terminate the string p1
	  line=p1; 
	  p1=p2+1; //set p1 past it for next round
      } else {
	 line=p1;
	 p1=NULL;
      }
	
      pos = strcspn(line, ":");
      if (pos < strlen(line)) {
	 st_net_dev_i = st_net_dev + dev;
	 st_net_dev_i->orig_buf=orig_buf;
	 strncpy(iface, line, MINIMUM(pos, MAX_IFACE_LEN - 1));
	 iface[MINIMUM(pos, MAX_IFACE_LEN - 1)] = '\0';
	 gettimeofday(&(st_net_dev_i->time), NULL);
	 sscanf(iface, "%s", st_net_dev_i->interface); /* Skip heading spaces */
	 sscanf(line + pos + 1, "%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld "
				"%lld %lld %lld %lld %lld %lld",
		&(st_net_dev_i->rx_bytes),
		&(st_net_dev_i->rx_packets),
		&(st_net_dev_i->rx_errors),
		&(st_net_dev_i->rx_dropped),
		&(st_net_dev_i->rx_fifo_errors),
		&(st_net_dev_i->rx_frame_errors),
		&(st_net_dev_i->rx_compressed),
		&(st_net_dev_i->multicast),
		&(st_net_dev_i->tx_bytes),
		&(st_net_dev_i->tx_packets),
		&(st_net_dev_i->tx_errors),
		&(st_net_dev_i->tx_dropped),
		&(st_net_dev_i->tx_fifo_errors),
		&(st_net_dev_i->collisions),
		&(st_net_dev_i->tx_carrier_errors),
		&(st_net_dev_i->tx_compressed));
	 dev++;
      }
   }
   max_dev = dev;
   return st_net_dev;
}

void complain(struct stats_net_dev *s1, struct stats_net_dev *s2, char *s, long long delta)
{
    printf("warn: counter %s on %s delta was %lld\n", s, s1->interface, delta);
    printf("%ld.%.6ld\n%s\n", s1->time.tv_sec, s1->time.tv_usec, s1->orig_buf);
    printf("%ld.%.6ld\n%s\n", s2->time.tv_sec, s2->time.tv_usec, s2->orig_buf);
    fflush(stdout);
}

#define DELTA(x) ((s2[i].x) - (s1[i].x))
#define DCOMPLAIN(x) if(DELTA(x) > DELTA_LIMIT) { complain(s1 + i, s2 + i, #x, DELTA(x)); error_count++; break; }
int main(int argc, char **argv)
{

    int error_count=0;
    struct stats_net_dev *s1, *s2;
    s1=read_net_dev_stat();
    while(error_count < ERROR_LIMIT) {
	s2=read_net_dev_stat();
	int i;
	for(i=0; i < max_dev; i++) {
	    DCOMPLAIN(rx_bytes);
	    DCOMPLAIN(rx_packets);
	    DCOMPLAIN(rx_errors);
	    DCOMPLAIN(rx_dropped);
	    DCOMPLAIN(rx_fifo_errors);
	    DCOMPLAIN(rx_frame_errors);
	    DCOMPLAIN(rx_compressed);
	    DCOMPLAIN(multicast);
	    DCOMPLAIN(tx_bytes);
	    DCOMPLAIN(tx_packets);
	    DCOMPLAIN(tx_errors);
	    DCOMPLAIN(tx_dropped);
	    DCOMPLAIN(tx_fifo_errors);
	    DCOMPLAIN(collisions);
	    DCOMPLAIN(tx_carrier_errors);
	    DCOMPLAIN(tx_compressed);
	}
	free(s1->orig_buf);
	free(s1);
	s1=s2;
	usleep(100000);
    }
    return 0;
}
