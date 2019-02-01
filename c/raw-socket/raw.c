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
    char * src_interface;
    char * des_interface;
} raw_param_t;

void* recv_u();
void* send_u(void *args);
unsigned short checksum(unsigned short* buff, int _16bitword);

int main(int argc, char** argv)
{
    pthread_t recv_id;
    pthread_t send_id;
    raw_param_t send_args;
    if(argc < 3)
    {
        printf("usage: app src_interface_name des_interface_name\n");
        return -1;
    }

    send_args.src_interface = argv[1];
    send_args.des_interface = argv[2];
    printf("test interface name: src = %s, des = %s\n", send_args.src_interface, send_args.des_interface);

    pthread_create(&recv_id, NULL, &recv_u, NULL);
    // sleep 2 seconds
    sleep(2);
    pthread_create(&send_id, NULL, &send_u, &send_args);
    
    pthread_join(recv_id, NULL);
    pthread_join(send_id, NULL);
    return 0;
}

void* recv_u()
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

    unsigned char *buffer = (unsigned char*)malloc(65536);  // to receive data
    memset(buffer, 0, 65536);
    struct sockaddr saddr;
    int saddr_len = sizeof(saddr);

    while(1)
    {
        // receive a network packet and copy in to buffer
        int buflen = recvfrom(sock_r, buffer, 65536, 0, &saddr, (socklen_t *)&saddr_len);
        if(buflen < 0)
        {
            printf("error in reading recvfrom function\n");
            close(sock_r);
            *ret = -1;
            return (void*)ret;
        }
        printf("buflen = %d\n", buflen);

        // ethernet header
        struct ethhdr *eth = (struct ethhdr *)(buffer);
        printf("Ethernet Header:\n");
        printf("\t|-Source address : %.2x-%.2x-%.2x-%.2x-%.2x-%.2x\n", eth->h_source[0], eth->h_source[1], eth->h_source[2], eth->h_source[3], eth->h_source[4], eth->h_source[5]);
        printf("\t|-Destination address : %.2x-%.2x-%.2x-%.2x-%.2x-%.2x\n", eth->h_dest[0], eth->h_dest[1], eth->h_dest[2], eth->h_dest[3], eth->h_dest[4], eth->h_dest[5]);
        printf("\t|-Protocol: %d\n", eth->h_proto); 

        // ip header
        struct sockaddr_in source, dest;
        unsigned short iphdrlen;
        struct iphdr *ip = (struct iphdr*)(buffer + sizeof(struct ethhdr));
        memset(&source, 0, sizeof(source));
        source.sin_addr.s_addr = ip->saddr;
        memset(&dest, 0, sizeof(dest));
        dest.sin_addr.s_addr = ip->daddr;

        printf("\t|-Version : %d\n",(unsigned int)ip->version);
        printf("\t|-Internet Header Length : %d DWORDS or %d Bytes\n",(unsigned int)ip->ihl,((unsigned int)(ip->ihl))*4);
        printf("\t|-Type Of Service : %d\n",(unsigned int)ip->tos);
        printf("\t|-Total Length : %d Bytes\n",ntohs(ip->tot_len));
        printf("\t|-Identification : %d\n",ntohs(ip->id));
        printf("\t|-Frag off: %d\n",ntohs(ip->frag_off));
        printf("\t|-Time To Live : %d\n",(unsigned int)ip->ttl);
        printf("\t|-Protocol : %d\n",(unsigned int)ip->protocol);
        printf("\t|-Header Checksum : %d\n",ntohs(ip->check));
        printf("\t|-Source IP : %s\n", inet_ntoa(source.sin_addr));
        printf("\t|-Destination IP : %s\n",inet_ntoa(dest.sin_addr));

        // transport layer header
        iphdrlen = ip->ihl * 4;
        struct udphdr *udp = (struct udphdr *)(buffer + iphdrlen + sizeof(struct ethhdr));
        
        printf("\t|-Source Port : %d\n", ntohs(udp->source));
        printf("\t|-Destination Port : %d\n", ntohs(udp->dest));
        printf("\t|-UDP Length : %d\n", ntohs(udp->len));
        printf("\t|-Source Checksum : %d\n", ntohs(udp->check));

        // extracting data
        unsigned char *data = (buffer + iphdrlen + sizeof(struct ethhdr) + sizeof(struct udphdr));
        int remaining_data = buflen - (iphdrlen + sizeof(struct ethhdr) + sizeof(struct udphdr));
        for(int i = 0; i < remaining_data; i++)
        {
            if(i != 0 && i % 16 == 0)
                printf("\n");
            printf("%.2x ", data[i]);
        } 
        break;
    }
    *ret = 0;
    return (void*)ret;
}


void* send_u(void* args)
{
    int *ret = (int*)malloc(sizeof(int));
    *ret = 0;
    raw_param_t *param =  (raw_param_t*)(args); 
    char *src_interface = param->src_interface;
    char *des_interface = param->des_interface;

    int sock_raw = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW);
    if(sock_raw == -1)
    {
        printf("error creating socket\n");
        *ret = -1;
        return (void*)ret;
    }

    // src index
    struct ifreq ifreq_i;
    memset(&ifreq_i, 0, sizeof(struct ifreq));
    strncpy(ifreq_i.ifr_name, src_interface, IFNAMSIZ-1); // giving name of Interface
    if((ioctl(sock_raw, SIOCGIFINDEX, &ifreq_i)) < 0) // getting index name
    {
        printf("error in index ioctl reading\n");
        close(sock_raw);
        *ret = -1;
        return (void*)ret;
    }
    printf("src index=%d\n", ifreq_i.ifr_ifru.ifru_ivalue);

    // des index 
    struct ifreq ifreq_i_d;
    memset(&ifreq_i_d, 0, sizeof(struct ifreq));
    strncpy(ifreq_i_d.ifr_name, des_interface, IFNAMSIZ-1); // giving name of Interface
    if((ioctl(sock_raw, SIOCGIFINDEX, &ifreq_i_d)) < 0) // getting index name
    {
        printf("error in index ioctl reading\n");
        close(sock_raw);
        *ret = -1;
        return (void*)ret;
    }
    printf("des index=%d\n", ifreq_i_d.ifr_ifru.ifru_ivalue);

    // src mac
    struct ifreq ifreq_c;
    memset(&ifreq_c, 0, sizeof(struct ifreq));
    strncpy(ifreq_c.ifr_name, src_interface, IFNAMSIZ-1); // giving name of Interface
    if((ioctl(sock_raw, SIOCGIFHWADDR, &ifreq_c)) < 0)  // getting mac address
    {
        printf("error in mac address ioctl reading\n");
        close(sock_raw);
        *ret = -1;
        return (void*)ret;
    }
    unsigned char *mac = (unsigned char *)malloc(14); 
    mac = ifreq_c.ifr_ifru.ifru_hwaddr.sa_data;
    printf("src mac=%.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    // des mac 
    struct ifreq ifreq_c_d;
    memset(&ifreq_c_d, 0, sizeof(struct ifreq));
    strncpy(ifreq_c_d.ifr_name, des_interface, IFNAMSIZ-1); // giving name of Interface
    if((ioctl(sock_raw, SIOCGIFHWADDR, &ifreq_c_d)) < 0)  // getting mac address
    {
        printf("error in mac address ioctl reading\n");
        close(sock_raw);
        *ret = -1;
        return (void*)ret;
    }
    mac = ifreq_c_d.ifr_ifru.ifru_hwaddr.sa_data;
    printf("src mac=%.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    // src ip
    struct ifreq ifreq_ip;
    memset(&ifreq_ip, 0, sizeof(struct ifreq));
    strncpy(ifreq_ip.ifr_name, src_interface, IFNAMSIZ-1); // giving name of Interface
    if((ioctl(sock_raw, SIOCGIFADDR, &ifreq_ip)) < 0)  // getting ip address
    {
        printf("error in ip address ioctl reading\n");
        close(sock_raw);
        *ret = -1;
        return (void*)ret;
    }
    printf("src ip=%s\n", inet_ntoa((((struct sockaddr_in *)&(ifreq_ip.ifr_ifru.ifru_addr))->sin_addr)));

    // des ip 
    struct ifreq ifreq_ip_d;
    memset(&ifreq_ip_d, 0, sizeof(struct ifreq));
    strncpy(ifreq_ip_d.ifr_name, des_interface, IFNAMSIZ-1); // giving name of Interface
    if((ioctl(sock_raw, SIOCGIFADDR, &ifreq_ip_d)) < 0)  // getting ip address
    {
        printf("error in ip address ioctl reading\n");
        close(sock_raw);
        *ret = -1;
        return (void*)ret;
    }
    printf("des ip=%s\n", inet_ntoa((((struct sockaddr_in *)&(ifreq_ip_d.ifr_ifru.ifru_addr))->sin_addr)));

    unsigned char* sendbuff = (unsigned char*)malloc(64);
    memset(sendbuff, 0, 64);

    struct ethhdr *eth = (struct ethhdr*)(sendbuff);
    // fill ethernet header, source mac
    eth->h_source[0] = (unsigned char)(ifreq_c.ifr_ifru.ifru_hwaddr.sa_data[0]);
    eth->h_source[1] = (unsigned char)(ifreq_c.ifr_ifru.ifru_hwaddr.sa_data[1]);
    eth->h_source[2] = (unsigned char)(ifreq_c.ifr_ifru.ifru_hwaddr.sa_data[2]);
    eth->h_source[3] = (unsigned char)(ifreq_c.ifr_ifru.ifru_hwaddr.sa_data[3]);
    eth->h_source[4] = (unsigned char)(ifreq_c.ifr_ifru.ifru_hwaddr.sa_data[4]);
    eth->h_source[5] = (unsigned char)(ifreq_c.ifr_ifru.ifru_hwaddr.sa_data[5]);

    // dest mac
    eth->h_dest[0] = (unsigned char)(ifreq_c_d.ifr_ifru.ifru_hwaddr.sa_data[0]);
    eth->h_dest[1] = (unsigned char)(ifreq_c_d.ifr_ifru.ifru_hwaddr.sa_data[1]);
    eth->h_dest[2] = (unsigned char)(ifreq_c_d.ifr_ifru.ifru_hwaddr.sa_data[2]);
    eth->h_dest[3] = (unsigned char)(ifreq_c_d.ifr_ifru.ifru_hwaddr.sa_data[3]);
    eth->h_dest[4] = (unsigned char)(ifreq_c_d.ifr_ifru.ifru_hwaddr.sa_data[4]);
    eth->h_dest[5] = (unsigned char)(ifreq_c_d.ifr_ifru.ifru_hwaddr.sa_data[5]);
    
    // protocol
    eth->h_proto = htons(ETH_P_IP); // means next header will be ip header
    // end of ethernet header
    int total_len = 0;
    total_len += sizeof(struct ethhdr);

    // constructing ip header
    struct iphdr *iph = (struct iphdr*)(sendbuff + sizeof(struct ethhdr));
    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 16;
    iph->id = htons(10201);
    iph->ttl = 64;
    iph->protocol = 17;
    iph->saddr = inet_addr(inet_ntoa((((struct sockaddr_in *)&(ifreq_ip.ifr_ifru.ifru_addr))->sin_addr)));
    iph->daddr = inet_addr(inet_ntoa((((struct sockaddr_in *)&(ifreq_ip_d.ifr_ifru.ifru_addr))->sin_addr)));
    total_len += sizeof(struct iphdr);

    // udp header
    struct udphdr *uh = (struct udphdr *)(sendbuff + sizeof(struct iphdr) + sizeof(struct ethhdr));
    uh->source = htons(23451);
    uh->dest = htons(23452);
    uh->check = 0;
    total_len += sizeof(struct udphdr);
    
    sendbuff[total_len++] = 0xaa;
    sendbuff[total_len++] = 0xbb;
    sendbuff[total_len++] = 0xcc;
    sendbuff[total_len++] = 0xdd;
    sendbuff[total_len++] = 0xee;

    // filling the remained fields
    // udp length field
    uh->len = htons((total_len - sizeof(struct iphdr) - sizeof(struct ethhdr)));
    // ip length field
    iph->tot_len = htons(total_len - sizeof(struct ethhdr));
    iph->check = checksum((unsigned short*)(sendbuff + sizeof(struct ethhdr)), (sizeof(struct iphdr)/2));

    // sending the packet
    struct sockaddr_ll saddr_ll;
    memset(&saddr_ll, 0, sizeof(struct sockaddr_ll));
    saddr_ll.sll_ifindex = ifreq_i.ifr_ifru.ifru_ivalue;    // index of interface
    saddr_ll.sll_halen = ETH_ALEN;    // length of destination mac address
    saddr_ll.sll_addr[0] = ifreq_c.ifr_ifru.ifru_hwaddr.sa_data[0];
    saddr_ll.sll_addr[1] = ifreq_c.ifr_ifru.ifru_hwaddr.sa_data[1];
    saddr_ll.sll_addr[2] = ifreq_c.ifr_ifru.ifru_hwaddr.sa_data[2];
    saddr_ll.sll_addr[3] = ifreq_c.ifr_ifru.ifru_hwaddr.sa_data[3];
    saddr_ll.sll_addr[4] = ifreq_c.ifr_ifru.ifru_hwaddr.sa_data[4];
    saddr_ll.sll_addr[5] = ifreq_c.ifr_ifru.ifru_hwaddr.sa_data[5];
/*
    saddr_ll.sll_addr[0] = ifreq_c_d.ifr_ifru.ifru_hwaddr.sa_data[0];
    saddr_ll.sll_addr[1] = ifreq_c_d.ifr_ifru.ifru_hwaddr.sa_data[1];
    saddr_ll.sll_addr[2] = ifreq_c_d.ifr_ifru.ifru_hwaddr.sa_data[2];
    saddr_ll.sll_addr[3] = ifreq_c_d.ifr_ifru.ifru_hwaddr.sa_data[3];
    saddr_ll.sll_addr[4] = ifreq_c_d.ifr_ifru.ifru_hwaddr.sa_data[4];
    saddr_ll.sll_addr[5] = ifreq_c_d.ifr_ifru.ifru_hwaddr.sa_data[5];
*/
    
    int send_len = sendto(sock_raw, sendbuff, 64, 0, (const struct sockaddr*)&saddr_ll, sizeof(struct sockaddr_ll));
    if(send_len < 0)
    {
        printf("error in sending ...sendlen=%d...errno=%d\n", send_len, errno);
        close(sock_raw);
        *ret = -1;
        return (void*)ret;
    }
}
    
unsigned short checksum(unsigned short* buff, int _16bitword)
{
    unsigned long sum;
    for(sum = 0; _16bitword > 0; _16bitword--)
    {
        sum += htons(*(buff)++);
        sum = ((sum >> 16) + (sum & 0xffff));
        sum += (sum >> 16);
    }
    return (unsigned short)(~sum);
} 
    
