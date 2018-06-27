#include <iostream>
#include <string.h>

using namespace std;

typedef unsigned char uint8_t;

int main()
{
/*
    uint8_t *buffer_ptr = new uint8_t[1024];
    memset(buffer_ptr, 0x36, 1024);
    for(int i = 0; i < 1024; i++)
    {
        if(i % 16 == 0)
            cout << "0x" << hex << i << "\t";
        cout << buffer_ptr[i] << " ";
        if(i > 0 && ((i + 1) % 16 == 0))
            cout << endl; 
    }

*/
    int cnt = 0;
    int loop = 0;
    uint8_t *buffer_ptr =  NULL;
    for(int loop = 0; loop < 1024; loop++)
    {
        buffer_ptr = new uint8_t[1024];
        cout << "buffer ptr " << (void *) buffer_ptr << endl;
        for(int i = 0; i < 1024; i++)
        {
            if( buffer_ptr[i] != 0)
            {
                cnt++;
                cout << "buffer ptr " << (void *) buffer_ptr << endl;
                cout << "have run " << loop << " times, non zero " << cnt << " times, error rate " << float(cnt) / float(loop * 1024 + i + 1) <<endl;
            }
        } 
    }

    return 0;
}
