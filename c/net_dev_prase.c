#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int link_detect_ns( char *eth_name, int *detected )
{
    int n_dev_len, ns_len = 0;
    char line[200];
    char ath0[120];
    char cmd[250];
    FILE *pipe;
    char *rets;
    char *token;

    strcpy( ath0, eth_name );
    n_dev_len = strlen( ath0 );
    if ( n_dev_len < 1 || n_dev_len > 120 )
    {
        printf( "dev length too long\n" );
        return -1;
    }

    memset( line, 0, sizeof( line ) );
    //sprintf( cmd, "ip netns exec %s ethtool %s | grep detect", ns0, ath0 );
    sprintf( cmd, "ethtool %s | grep detect", ath0 );
    pipe = popen( cmd, "r" );
    if ( !pipe )
    {
        printf("Failed to open pipe, cmd: %s\n", cmd);
        return -1;
    }

    rets = fgets( line, sizeof( line ), pipe );
    if( rets != NULL )
    {
        char* pointer;
        token = strtok_r( line, " ", &pointer );
        printf("token %s\n", token);
        token = strtok_r( NULL, " ", &pointer );
        printf("token %s\n", token);
        token = strtok_r( NULL, " ", &pointer );
        printf("token %s\n", token);
    }
    else
    {
        pclose( pipe );
        printf("interface %s not exitst\n", ath0);
        return -1;
    }

    if( memcmp( token, "no", 2 ) == 0 )
    {
        *detected = 0;
    }
    else if( memcmp( token, "yes", 3 ) == 0 )
    {
        *detected = 1;
    }
    else
    {
        pclose( pipe );
        *detected = 2;
        return -1;
    }
    pclose( pipe );
    return 0;
}

int tx_rx_stat( char *eth_name, double *recv, double *send )
{
    int nDevLen, fd, nBytes, i = 0;
    char *p, * pDev, *ifconfig_value;
    long rx_tx[2];
    char buf[1024 * 1024];
    char ath0[120];
    char cmd[250];
    FILE *pipe;
    char *rets;
    int ret = 0;

    //strcpy(ath0, eth_name);
    memset( ath0, 0, sizeof( ath0 ) );
    sprintf( ath0, "%s:", eth_name );

    nDevLen = strlen( ath0 );
    if ( nDevLen < 1 || nDevLen > 120 )
    {
        printf( "dev length too long\n" );
        return -1;
    }

    memset( buf, 0, sizeof( buf ) );
    sprintf( cmd, "cat /proc/net/dev | grep %s", ath0 );

    pipe = popen( cmd, "r" );
    if ( !pipe )
    {
        printf( "%s fail!\n", cmd );
        return -1;
    }

    rets = fgets( buf, sizeof( buf ) - 1, pipe );

    if( rets != NULL )
    {
        printf("buf: \"%s\"", buf );

        for ( p = strtok( buf, " \t\r\n" ); p; p = strtok( NULL, " \t\r\n" ) )
        {
            i++;
            ifconfig_value = ( char* )malloc( 20 );
            strcpy( ifconfig_value, p );

            if( i == 3 )
            {
                rx_tx[0] = atol( ifconfig_value );
                *recv = ( double )rx_tx[0];
            }

            if( i == 11 )
            {
                rx_tx[1] = atol( ifconfig_value );
                *send = ( double )rx_tx[1];
                free( ifconfig_value );
                break;
            }
            free( ifconfig_value );
        }
    }
    else
    {
        pclose( pipe );
        printf( "Link is down! %s not exist!\n", ath0 );
        return -1;
    }

    pclose( pipe );

    return 0;
}

int tx_rx_stat_fd( char *eth_name, double *recv, double *send )
{
    int nDevLen, fd, nBytes, i = 0;
    char *p, * p_dev, *ifconfig_value;
    long rx_tx[2];
    char buf[1024 * 12];
    char ath0[120];

    strcpy( ath0, eth_name ); nDevLen = strlen( ath0 );
    if ( nDevLen < 1 || nDevLen > 120 )
    {
        printf( "dev length too long" );
        return -1;
    }
    fd = open( "/proc/net/dev", O_RDONLY | O_EXCL );
    if ( -1 == fd )
    {
        printf("Failed to open /proc/net/dev");
        return -1;
    }

    memset( buf, 0, sizeof( buf ) );
    lseek( fd, 0, SEEK_SET );
    nBytes = read( fd, buf, sizeof( buf ) - 1 );
    if ( -1 == nBytes )
    {
        printf("Failed to read /proc/net/dev");
        close( fd );
        return -1;
    }
    buf[nBytes] = '\0';

    p_dev = strstr( buf, ath0 );
    if ( NULL == p_dev )
    {
        printf("don't find dev");
        close( fd );
        return -1;
    }

    char* pointer;
    for ( p = strtok_r( p_dev, " \t\r\n", &pointer ); p; p = strtok_r( NULL, " \t\r\n", &pointer ) )
    {
        i++;
        ifconfig_value = ( char* )malloc( 20 );
        strcpy( ifconfig_value, p );

        if( i == 3 )
        {
            rx_tx[0] = atol( ifconfig_value );
            *recv = ( double )rx_tx[0];
        }
        if( i == 11 )
        {
            rx_tx[1] = atol( ifconfig_value );
            *send = ( double )rx_tx[1];
            free( ifconfig_value );
            break;
        }
        free( ifconfig_value );
    }

    close( fd );

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///
///   @brief   get rx tx stat by bytes
int main(int argc, char* argv[])
{
    char eth_name[100];
    strcpy(eth_name, "eth0");
    if(argc > 1)
        strcpy(eth_name, argv[1]);
        //sprintf(eth_name , "%s", argv[1]);
    printf("eth name: %s\n", eth_name);

    double recv = 0, send = 0;
    int ret = tx_rx_stat( eth_name, &recv, &send );
    printf("ret: %d, recv = %f, send = %f\n", ret, recv, send);

    int ret1 = tx_rx_stat_fd( eth_name, &recv, &send );
    printf("ret1: %d, recv = %f, send = %f\n", ret1, recv, send);

    int detected;
    int ret2 = link_detect_ns( eth_name, &detected );
    printf("ret2: %d, detected = %d\n", ret2, detected);
        
    return 0;
}
