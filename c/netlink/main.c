#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_infiniband.h>
#include <linux/version.h>
#include <time.h>
#include <errno.h>
#include <syslog.h>
#include <sched.h>
#include <pthread.h>
#include <termios.h>

#include <stdarg.h>
#include <fcntl.h>
#include <stddef.h>
#include <strings.h>
#include <string.h>
#include <signal.h>

int run();

int main()
{
	int ret = 0;
	
	ret = run();
	printf("1 ret = %d\n", ret);
	ret = run();
	printf("2 ret = %d\n", ret);
	ret = run();
	printf("3 ret = %d\n", ret);


	return 0;

}

int run()
{
    fd_set rfds;
    int retval;
    struct sockaddr_nl addr;

    // Open netlink socket for netlink route message groups
    int nl_socket = socket( AF_NETLINK, SOCK_RAW, NETLINK_ROUTE );
	printf("nl_sockdt %d\n", nl_socket );

    if( nl_socket < 0 )
    {
		printf("error opening netlink socket!\n");
		return -1;
    }
    int enable = 1;
    if( setsockopt ( nl_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int) ) < 0 )
	{
        printf("setsockopt for reuse failed\n");
		return -2 ;
	}

    memset( ( void * )&addr, 0, sizeof( addr ) );

    addr.nl_family = AF_NETLINK;
    addr.nl_pid = getpid();
    addr.nl_groups = RTMGRP_LINK | RTMGRP_IPV4_IFADDR | RTMGRP_IPV6_IFADDR;
    printf("nl_pid = getpid = %d\n", addr.nl_pid);

    int ret = bind( nl_socket, ( struct sockaddr * )&addr, sizeof( addr ) );
    if( ret  < 0 )
    {
		printf("bind ret value %d\n", ret);
        close( nl_socket );
        printf("failed to bind to netlink socket!");
		return -3;
    }
	close(nl_socket);
	return 0;
}
