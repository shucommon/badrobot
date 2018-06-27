#include<stdio.h>
#include<string.h>
#include<iostream>

using namespace std;

int main()
{
    char cmd[50];
    char *token;
    char buf[100];
    char log_buf[100];
	char str[18] = "12 34:56:ab:cd:ef";
	int num = 0;
	int en[6];
    FILE *pipe;
    char *rets;
    int i;
	
    // check link status
    memset( cmd, 0, sizeof(cmd) );
    sprintf( cmd, "ethtool %s | grep detected", "eth0" );
    pipe = popen( cmd, "r" );
    if( !pipe )
    {
        printf("open pipe error: %s\n", cmd);
    }
 
    memset( buf, 0, sizeof(buf) );
    rets = fgets( buf, sizeof(buf), pipe );
    memcpy(log_buf, buf, sizeof(rets));
    if( rets != NULL )
    {
        char *ptr;
        strtok_r( buf, " ", &ptr);
        printf("token %s\n", token);
        strtok_r( NULL, " ", &ptr);
        printf("token %s\n", token);
        token = strtok_r( NULL, " ", &ptr);
        printf("token %s\n", token);
    }
    cout << "buf-" << buf << ", token-" << token << endl;
    cout << "rets-" << log_buf << endl;

	num = sscanf(str, "%02x %02x:%02x:%02x:%02x:%02x", 
				&en[0], &en[1], &en[2], &en[3], &en[4], &en[5]);
	for(i = 0; i < 6; i++)
	{
		printf("en[%d] = %x\n", i, en[i]);
	}


    
	return 0;
}
