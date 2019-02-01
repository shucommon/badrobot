#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <time.h>
#include <sys/ioctl.h>
#include <net/if.h>

// namespace
#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <sched.h>
#include <fcntl.h>

#define handle_error_en(en, msg) \
                   do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
                   do { perror(msg); exit(EXIT_FAILURE); } while (0)

struct thread_info      /* Used as argument to thread_start() */
{
    pthread_t thread_id;        /* ID returned by pthread_create() */
    int       thread_num;       /* Application-defined thread # */
    struct sockaddr_in serv_addr;
};

/*
 * tcp server
 */
void * tcp_server(void *arg)
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;
    struct ifreq ifr;

    char sendBuff[1025];
    time_t ticks;

    struct thread_info *tinfo = arg;
    int ret = 0;

    int len=20;
    char buffer[len];
    int fd;
    fd = open("/var/run/netns/port1", O_RDONLY);
    if (fd == -1)
    {
        ret = -1;
        pthread_exit(&ret);
    }

    if (setns(fd, 0) == -1)         /* Join that namespace */
    {
        ret = -1;
        pthread_exit(&ret);
    }

    inet_ntop(AF_INET, &(tinfo->serv_addr.sin_addr.s_addr), buffer, len);
    printf( "Thread %d: tcp server created, ip: %s, port: %d\n", tinfo->thread_num, buffer, tinfo->serv_addr.sin_port);

    listenfd = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP);
    memset( &serv_addr, '0', sizeof( serv_addr ) );
    memset( sendBuff, '0', sizeof( sendBuff ) );

    memset(&ifr, 0, sizeof(ifr));
    snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "eth4");
    if (setsockopt(listenfd, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) < 0) {
        printf( "\n Error : Could not set socket opt \n" );
        ret = -1;
        pthread_exit(&ret);
    }

    serv_addr.sin_family = tinfo->serv_addr.sin_family;
    serv_addr.sin_addr.s_addr = tinfo->serv_addr.sin_addr.s_addr;
    serv_addr.sin_port = tinfo->serv_addr.sin_port;

    bind( listenfd, ( struct sockaddr* )&serv_addr, sizeof( serv_addr ) );

    listen( listenfd, 10 );

    while( 1 )
    {
        connfd = accept( listenfd, ( struct sockaddr* )NULL, NULL );
        do{
            ticks = time( NULL );
            snprintf( sendBuff, sizeof( sendBuff ), "%.24s\r\n", ctime( &ticks ) );
            write( connfd, sendBuff, strlen( sendBuff ) );

            printf("server send message out\n");
//        close( connfd );
            sleep( 1 );
        }while(1);
    }

    ret = 0;
    pthread_exit(&ret);
}

/*
 * tcp clent 
 */
void * tcp_client(void *arg)
{
    int sockfd = 0, n = 0;
    char recvBuff[1024];
    struct sockaddr_in serv_addr;
    struct ifreq ifr;

    struct thread_info *tinfo = arg;
    int ret = 0;
    int retry = 0;

    int fd;
    fd = open("/var/run/netns/port2", O_RDONLY);
    if (fd == -1)
    {
        ret = -1;
        pthread_exit(&ret);
    }
        

    if (setns(fd, 0) == -1)         /* Join that namespace */
    {
        ret = -1;
        pthread_exit(&ret);
    }

    printf( "Thread %d: tcp_client created\n", tinfo->thread_num);

    memset( recvBuff, '0', sizeof( recvBuff ) );
    if( ( sockfd = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP) ) < 0 )
    {
        printf( "\n Error : Could not create socket \n" );
        ret = -1;
        pthread_exit(&ret);
    }
    memset(&ifr, 0, sizeof(ifr));
    snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "eth5");
    if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) < 0) {
        printf( "\n Error : Could not set socket opt \n" );
        close(sockfd);
        ret = -1;
        pthread_exit(&ret);
    }

    memset( &serv_addr, '0', sizeof( serv_addr ) );

    serv_addr.sin_family = tinfo->serv_addr.sin_family;
    serv_addr.sin_port = tinfo->serv_addr.sin_port;
    serv_addr.sin_addr.s_addr = tinfo->serv_addr.sin_addr.s_addr;

    while( connect( sockfd, ( struct sockaddr * )&serv_addr, sizeof( serv_addr ) ) < 0 )
    {
        if(retry++ > 5)
        {
            printf( "\n Error : Connect Failed \n" );
            close(sockfd);
            ret = -1;
            pthread_exit(&ret);
        }
        sleep(1);
    }

    while ( ( n = read( sockfd, recvBuff, sizeof( recvBuff ) - 1 ) ) > 0 )
    {
        recvBuff[n] = 0;
        printf("client receive: ");
        if( fputs( recvBuff, stdout ) == EOF )
        {
            printf( "\n Error : Fputs error\n" );
        }
    }

    if( n < 0 )
    {
        printf( "\n Read error \n" );
    }

    close(sockfd);
    ret = 0;
    pthread_exit(&ret);
}

int main( int argc, char *argv[] )
{
    int s, tnum, opt;
    struct thread_info *tinfo;
    pthread_attr_t attr;
    int stack_size;
    void *res;
    int port=5000;

    /* The "-s" option specifies a stack size for our threads */

    stack_size = -1;
    while ( ( opt = getopt( argc, argv, "p:s:a" ) ) != -1 )
    {
        switch ( opt )
        {
        case 's':
            stack_size = strtoul( optarg, NULL, 0 );
            break;

        case 'p':
            port = strtoul( optarg, NULL, 0 );
            break;

        default:
            fprintf( stderr, "Usage: %s [-s stack-size] arg...\n",
                     argv[0] );
            exit( EXIT_FAILURE );
        }
    }

    /* Initialize thread creation attributes */

    s = pthread_attr_init( &attr );
    if ( s != 0 )
        handle_error_en( s, "pthread_attr_init" );

    if ( stack_size > 0 )
    {
        s = pthread_attr_setstacksize( &attr, stack_size );
        if ( s != 0 )
            handle_error_en( s, "pthread_attr_setstacksize" );
    }

    /* Allocate memory for pthread_create() arguments */
    tinfo = calloc( 2, sizeof( struct thread_info ) );
    if ( tinfo == NULL )
        handle_error( "calloc" );

    tinfo[0].thread_num = 1;
    tinfo[0].serv_addr.sin_family = AF_INET; 
    tinfo[0].serv_addr.sin_port = port; 
    tinfo[0].serv_addr.sin_addr.s_addr = inet_addr("192.168.2.10");
    s = pthread_create( &tinfo[0].thread_id, &attr, &tcp_server, &tinfo[0] );
    if ( s != 0 )
        handle_error_en( s, "pthread_create failed for tcp_server" );

    tinfo[1].thread_num = 2;
    tinfo[1].serv_addr.sin_family = AF_INET; 
    tinfo[1].serv_addr.sin_port = port; 
    tinfo[1].serv_addr.sin_addr.s_addr = inet_addr("192.168.2.10"); 
    s = pthread_create( &tinfo[1].thread_id, &attr, &tcp_client, &tinfo[1] );
    if ( s != 0 )
        handle_error_en( s, "pthread_create failed for tcp_client" );

    /* Destroy the thread attributes object, since it is no
     *               longer needed */

    s = pthread_attr_destroy( &attr );
    if ( s != 0 )
        handle_error_en( s, "pthread_attr_destroy" );

    /* Now join with each thread, and display its returned value */

    for ( tnum = 0; tnum < 2; tnum++ )
    {
        s = pthread_join( tinfo[tnum].thread_id, &res );
        if ( s != 0 )
            handle_error_en( s, "pthread_join" );

        printf( "Joined with thread %d; returned value was %d\n",
                tinfo[tnum].thread_num,  *(int *)res );
    }

    free( tinfo );
    exit( EXIT_SUCCESS );
}
