#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int tx_rx_stat( char *eth_name, double *recv, double *send )
{
    int nDevLen, fd, nBytes, i = 0;
    char *p, * pDev, *ifconfig_value;
    long rx_tx[2];
    char buf[1024];
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

int main()
{
    char * eth_name = "eth0";
    double recv = 0, send = 0;
    int ret = tx_rx_stat( eth_name, &recv, &send );
    printf("ret: %d, recv = %f, send = %f\n", ret, recv, send);

    return 0;
}
