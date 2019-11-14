#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/ip.h>
#include <netinet/in.h>
#include <netpacket/packet.h>
#include <arpa/inet.h>
#include <linux/udp.h>
#include <linux/if_ether.h>
#include <net/if.h>
#include <net/ethernet.h>

typedef struct raw_param
{
    int total_len;
    char ** intf;
} raw_param_t;

typedef unsigned long long int  uint64;
typedef unsigned int uint32;
#define PROC_NET_DEV "/proc/net/dev"
#define _NAME_MAX_LEN 256
/**
  @struct       __net_dev_stats_t
  @brief        network device statistics
*/
struct __net_dev_stats_t {
    uint64   rx_bytes;      /**< number of rx packets         */
    uint64   rx_packets;    /**< number of rx packets         */
    uint32   rx_errors;     /**< number of rx error packets   */
    uint32   rx_dropped;    /**< number of rx dropped packets */
    uint32   rx_overrun;    /**< number of rx overrun packets */
    uint32   rx_frame;      /**< number of rx frame packets   */
    uint32   rx_compressed; /**< number of rx compressed packets */
    uint32   rx_mcast;      /**< number of rx mcast packets   */

    uint64   tx_bytes;      /**< number of tx packets         */
    uint64   tx_packets;    /**< number of tx packets         */
    uint32   tx_errors;     /**< number of tx error packets   */
    uint32   tx_dropped;    /**< number of tx dropped packets */
    uint32   tx_overrun;    /**< number of tx overrun packets */
    uint32   tx_collision;  /**< number of tx collisions      */
    uint32   tx_carrier;    /**< number of tx carrier packets */
    uint32   tx_compressed; /**< number of tx compressed packets */
};  
typedef struct __net_dev_stats_t net_dev_stats_t;

int bring_up_intf(char * intf);
int find_intf(char **intf, uint8_t *size, int did);
int get_status(char * interface, net_dev_stats_t *stat);
unsigned char * get_mac(int sock, unsigned char *interface);
int recv_intf(int sock_r, char *src_interface, char *des_interface, int len);
int send_intf(int sock_raw, char * src_interface, char *des_interface, int len);
void* recv_u(void *args);
void* send_u(void *args);

int main(int argc, char** argv)
{
    pthread_t recv_id;
    pthread_t send_id;
    raw_param_t sock_args;
    void *ret1, *ret2;

    char **intf = (char **)malloc(sizeof(char *) * 4);
    uint8_t size;
    if(find_intf(intf, &size, 0x15ab) != 0) {
        printf("Failed to find interface to test\n");
        return -1;
    }
    sock_args.intf = intf;
    sock_args.total_len = 64;

    pthread_create(&recv_id, NULL, &recv_u, &sock_args);
    // sleep 2 seconds
    sleep(2);
    pthread_create(&send_id, NULL, &send_u, &sock_args);

    pthread_join(recv_id, &ret1);
    pthread_join(send_id, &ret2);
    printf("ret1 %d, ret2 %d\n", *(int *)ret1, *(int *)ret2);
    return 0;
}

int bring_up_intf(char * intf)
{
    // bring up interface
    uint8_t retry = 5;
    while(1) {
        char sys_cmd[_NAME_MAX_LEN];
        memset(sys_cmd, 0, _NAME_MAX_LEN);
        snprintf(sys_cmd, _NAME_MAX_LEN, "ifconfig | grep %s", intf);
        if(system(sys_cmd) != 0) {
            if(retry-- == 0) {
                printf("Ethernet interface %s is not up.\n", intf);
                return -1;
            }
            printf("trying to bring up interface %s, retry %u times\n", intf, 5 - retry);
            char cmd[_NAME_MAX_LEN];
            memset(cmd, 0, _NAME_MAX_LEN);
            snprintf(cmd, _NAME_MAX_LEN, "ifconfig %s up", intf);
            system(cmd);
            sleep(2);
        } else {
            printf("Ethernet interface %s is up\n", intf);
            break;
        }
    }
    return 0;
}

/*
/sys/class/net/eth2/device/device:0x15ab
/sys/class/net/eth3/device/device:0x15ab
/sys/class/net/eth4/device/device:0x15ab
/sys/class/net/eth5/device/device:0x15ab
*/
int find_intf(char **intf, uint8_t *size, int did)
{
    char cmd[64];
    snprintf(cmd, 64, "grep -r '%x' /sys/class/net/*/device/device", did);
    FILE *fp = popen(cmd, "r");
    if(fp == NULL) {
        printf("Failed open pipe to run cmd : %s\n", cmd);
        return -1;
    }

    char buf[1024];
    uint8_t index = 0;
    while(fgets(buf, sizeof(buf), fp) != NULL) {
        char *start = strstr(buf, "eth");
        if(start == NULL) {
            printf("Error in parse interface name\n");
            pclose(fp);
            return -1;
        }
        char *end = strstr(buf, "/device");
        if(end == NULL) {
            printf("Error in parse interface name\n");
            pclose(fp);
            return -1;
        }
        uint8_t len = end - start;
        char *interf = (char *)malloc(sizeof(char) * (len + 1));
        snprintf(interf, len+1, "%s", start);
        intf[index] = interf;
        index++;
    }
    if(index != 4) {
        printf("Failed to find all ethernet interface\n");
        pclose(fp);
        return -1;
    }
    *size = 4;
    pclose(fp);
    return 0;
}

int get_status(char * interface, net_dev_stats_t *stat)
{
    FILE *fp;
    int nscan = 0;
    char fbuf[512];
    if(interface == NULL) {
        printf("Network interface not defined!\n");
        return -1;
    }

    /*
    Inter-|   Receive                                                |  Transmit
    face  |bytes    packets errs drop fifo frame compressed multicast|bytes    packets errs drop fifo colls carrier compressed
    eth0:       0       0    0    0    0     0          0         0        0       0    0    0    0     0       0          0
    eth1: 1537488   33118    0    0    0     0          0        19  8741407   70645    0    0    0     0       0          0
    */
    fp = fopen(PROC_NET_DEV, "r");
    if(!fp) {
        printf("Unable to open %s for reading\n", PROC_NET_DEV);
        return -1;
    }

    // skip first two lines
    fgets(fbuf, sizeof(fbuf), fp);
    fgets(fbuf, sizeof(fbuf), fp);

    while(fgets(fbuf, sizeof(fbuf), fp)) {
        char * stats = strchr(fbuf, ':');
        char dev[32];
        *stats = '\0';
        stats++;
        sscanf(fbuf, "%s", dev);
        if(!strcmp(dev, interface)) {
            nscan = sscanf(stats, "%llu %llu %u %u %u %u %u %u %llu %llu %u %u %u %u %u %u",
                               &stat->rx_bytes,
                               &stat->rx_packets,
                               &stat->rx_errors,
                               &stat->rx_dropped,
                               &stat->rx_overrun,
                               &stat->rx_frame,
                               &stat->rx_compressed,
                               &stat->rx_mcast,
                               &stat->tx_bytes,
                               &stat->tx_packets,
                               &stat->tx_errors,
                               &stat->tx_dropped,
                               &stat->tx_overrun,
                               &stat->tx_collision,
                               &stat->tx_carrier,
                               &stat->tx_compressed);
            if(nscan != 16) {
                printf("Unable to parse %s.\n", PROC_NET_DEV);
                fclose(fp);
                return -1;
            }
            printf("%s stats: %llu %llu %u %u %u %u %u %u %llu %llu %u %u %u %u %u %u\n",
                       dev,
                       stat->rx_bytes,
                       stat->rx_packets,
                       stat->rx_errors,
                       stat->rx_dropped,
                       stat->rx_overrun,
                       stat->rx_frame,
                       stat->rx_compressed,
                       stat->rx_mcast,
                       stat->tx_bytes,
                       stat->tx_packets,
                       stat->tx_errors,
                       stat->tx_dropped,
                       stat->tx_overrun,
                       stat->tx_collision,
                       stat->tx_carrier,
                       stat->tx_compressed);
            break;
        }
    }
    if(!nscan) {
        printf("Unable to find %s interface in %s.\n", interface, PROC_NET_DEV);
        fclose(fp);
        return -1;
    }
    fclose(fp);
    return 0;
}

unsigned char * get_mac(int sock, unsigned char *interface)
{
    struct ifreq ifreq_c;
    memset(&ifreq_c, 0, sizeof(struct ifreq));
    strncpy(ifreq_c.ifr_name, interface, IFNAMSIZ-1);
    if((ioctl(sock, SIOCGIFHWADDR, &ifreq_c)) < 0)
    {
        printf("error in mac address ioctl reading\n");
        return NULL;
    }
    unsigned char *mac = (unsigned char *)malloc(ETH_ALEN + 1);
    if(mac == NULL)
    {
        printf("error malloc mac buffer\n");
        return NULL;
    }
    memcpy((void *)mac, (void *)(ifreq_c.ifr_ifru.ifru_hwaddr.sa_data), ETH_ALEN);
    return mac;
}

int recv_intf(int sock_r, char *src_interface, char *des_interface, int len)
{
    unsigned char *buffer = (unsigned char*)malloc(65536);  // to receive data
    memset(buffer, 0, 65536);
    struct sockaddr saddr;
    int saddr_len = sizeof(saddr);

    while(1)
    {
        // receive a network packet and copy into buffer
        int buflen = recvfrom(sock_r, buffer, 65536, 0, &saddr, (socklen_t *)&saddr_len);
        if(buflen < 0)
        {
            printf("error in reading recvfrom function\n");
            return -1;
        }

        // ethernet header
        struct ethhdr *eth = (struct ethhdr *)(buffer);

        // src mac verify
        unsigned char * src_mac = get_mac(sock_r, src_interface);
        if(src_mac == NULL)
        {
            printf("error in get src mac address\n");
            return -1;
        }
        if(strncmp(eth->h_source, src_mac, ETH_ALEN))
            continue;

        // des mac verify
        unsigned char * des_mac = get_mac(sock_r, des_interface);
        if(des_mac == NULL)
        {
            printf("error in get des mac address\n");
            return -1;
        }
        if(strncmp(eth->h_dest, des_mac, ETH_ALEN))
            continue;

        // verify len
        if(buflen != len)
            continue;

        printf("Receive packet:\n");
        printf("\t|-Packet total len : %d\n", buflen);
        printf("\t|-Source address : %.2x-%.2x-%.2x-%.2x-%.2x-%.2x\n", eth->h_source[0], eth->h_source[1], eth->h_source[2], eth->h_source[3], eth->h_source[4], eth->h_source[5]);
        printf("\t|-Destination address : %.2x-%.2x-%.2x-%.2x-%.2x-%.2x\n", eth->h_dest[0], eth->h_dest[1], eth->h_dest[2], eth->h_dest[3], eth->h_dest[4], eth->h_dest[5]);
        printf("\t|-Data:\t");

        // extracting data
        unsigned char *data = (buffer + sizeof(struct ethhdr));
        int remaining_data = buflen - sizeof(struct ethhdr);
        for(int i = 0; i < remaining_data; i++)
        {
            if(i != 0 && i % 16 == 0)
                printf("\n\t\t");
            printf("0x%.2x ", data[i]);
        }
        printf("\n");

        unsigned char start_pattern = 0;
        for(int i = 0; i < remaining_data; i++) {
            if(data[i] != start_pattern) {
                printf("receive data verify failed\n");
                return -1;
            }
            start_pattern += 0x11;
        }
        printf("receive data verify success\n");
        net_dev_stats_t stat;
        get_status(src_interface, &stat);
        get_status(des_interface, &stat);
        break;
    }
    return 0;
}

void* recv_u(void *args)
{
    int *ret = (int*)malloc(sizeof(int));
    *ret = 0;
    // step 1, opening a raw socket
    int sock_r;
    sock_r = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if(sock_r < 0)
    {
        printf("error creating socket\n");
        *ret = -1;
        return (void*)ret;
    }

    raw_param_t *param =  (raw_param_t*)(args);
    char *src_interface = param->intf[0];
    char *des_interface = param->intf[1];
    int len = param->total_len;
    if(recv_intf(sock_r, src_interface, des_interface, len)) {
        printf("receive from %s on %s failed\n", des_interface, src_interface);
        close(sock_r);
        *ret = -1;
        return (void*)ret;
    }

    src_interface = param->intf[1];
    des_interface = param->intf[0];
    if(recv_intf(sock_r, src_interface, des_interface, len)) {
        printf("receive from %s on %s failed\n", des_interface, src_interface);
        close(sock_r);
        *ret = -1;
        return (void*)ret;
    }

    src_interface = param->intf[2];
    des_interface = param->intf[3];
    if(recv_intf(sock_r, src_interface, des_interface, len)) {
        printf("receive from %s on %s failed\n", des_interface, src_interface);
        close(sock_r);
        *ret = -1;
        return (void*)ret;
    }

    src_interface = param->intf[3];
    des_interface = param->intf[2];
    if(recv_intf(sock_r, src_interface, des_interface, len)) {
        printf("receive from %s on %s failed\n", des_interface, src_interface);
        close(sock_r);
        *ret = -1;
        return (void*)ret;
    }

    *ret = 0;
    close(sock_r);
    return (void*)ret;
}

int send_intf(int sock_raw, char * src_interface, char *des_interface, int len)
{
    if(bring_up_intf(src_interface) != 0) {
        return -1;
    }
    if(bring_up_intf(des_interface) != 0) {
        return -1;
    }

    // src index
    struct ifreq ifreq_i;
    memset(&ifreq_i, 0, sizeof(struct ifreq));
    strncpy(ifreq_i.ifr_name, src_interface, IFNAMSIZ-1); // giving name of Interface
    if((ioctl(sock_raw, SIOCGIFINDEX, &ifreq_i)) < 0) // getting index name
    {
        printf("error in index ioctl reading\n");
        return -1;
    }

    // src mac
    unsigned char * src_mac = get_mac(sock_raw, src_interface);
    if(src_mac == NULL)
    {
        printf("error in get src mac address\n");
        return -1;
    }

    // des mac
    unsigned char * des_mac = get_mac(sock_raw, des_interface);
    if(des_mac == NULL)
    {
        printf("error in get des mac address\n");
        return -1;
    }

    unsigned char* sendbuff = (unsigned char*)malloc(len);
    memset(sendbuff, 0, len);

    struct ethhdr *eth = (struct ethhdr*)(sendbuff);
    // fill ethernet header, source mac
    memcpy((void *)(eth->h_source), (void *)src_mac, ETH_ALEN);
    // fill ethernet header, dest mac
    memcpy((void *)(eth->h_dest), (void *)des_mac, ETH_ALEN);
    // fill ethernet header, protocol, this field is not used
    eth->h_proto = htons(0x1234);

    // fill in data after ethernet header
    int total_len = sizeof(struct ethhdr);
    unsigned char start_pattern = 0;
    for(; total_len < len; total_len++) {
        sendbuff[total_len] = start_pattern;
        start_pattern += 0x11;
    }

    // sending the packet
    struct sockaddr_ll saddr_ll;
    memset(&saddr_ll, 0, sizeof(struct sockaddr_ll));
    saddr_ll.sll_family = PF_PACKET;
    saddr_ll.sll_ifindex = ifreq_i.ifr_ifru.ifru_ivalue;    // index of interface
    saddr_ll.sll_halen = ETH_ALEN;    // length of destination mac address
    memcpy((void *)(saddr_ll.sll_addr), (void *)des_mac, ETH_ALEN);

    int send_len = sendto(sock_raw, sendbuff, len, 0, (const struct sockaddr*)&saddr_ll, sizeof(struct sockaddr_ll));
    if(send_len < 0)
    {
        printf("error in sending ...sendlen=%d...errno=%d\n", send_len, errno);
        return -1;
    }
    return 0;
}

void* send_u(void* args)
{
    int *ret = (int*)malloc(sizeof(int));
    *ret = 0;
    raw_param_t *param =  (raw_param_t*)(args);
    char *src_interface = param->intf[0];
    char *des_interface = param->intf[1];
    int len = param->total_len;

    int sock_raw = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW);
    if(sock_raw == -1)
    {
        printf("error creating socket\n");
        *ret = -1;
        return (void*)ret;
    }

    printf("Sending 1 packet %d bytes from %s to %s\n", len, src_interface, des_interface);
    if(send_intf(sock_raw, src_interface, des_interface, len)) {
        printf("Error sending packet from %s to %s\n", src_interface, des_interface);
        *ret = -1;
        return (void*)ret;
    }
    sleep(1);

    src_interface = param->intf[1];
    des_interface = param->intf[0];
    printf("Sending 1 packet %d bytes from %s to %s\n", len, src_interface, des_interface);
    if(send_intf(sock_raw, src_interface, des_interface, len)) {
        printf("Error sending packet from %s to %s\n", src_interface, des_interface);
        *ret = -1;
        return (void*)ret;
    }
    sleep(1);

    src_interface = param->intf[2];
    des_interface = param->intf[3];
    printf("Sending 1 packet %d bytes from %s to %s\n", len, src_interface, des_interface);
    if(send_intf(sock_raw, src_interface, des_interface, len)) {
        printf("Error sending packet from %s to %s\n", src_interface, des_interface);
        *ret = -1;
        return (void*)ret;
    }
    sleep(1);

    src_interface = param->intf[3];
    des_interface = param->intf[2];
    printf("Sending 1 packet %d bytes from %s to %s\n", len, src_interface, des_interface);
    if(send_intf(sock_raw, src_interface, des_interface, len)) {
        printf("Error sending packet from %s to %s\n", src_interface, des_interface);
        *ret = -1;
        return (void*)ret;
    }

    close(sock_raw);
    *ret = 0;
    return (void*)ret;
}
