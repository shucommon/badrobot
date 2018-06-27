#include<iostream>
#include<string>

using namespace std;

int main()
{
    string test = "";
    if(test.empty())
        cout << "empty\n";
    else
        cout << "hh\n";

    unsigned int suffix = 0;
    string mbi = "blade_mbi.bin";
    
    for(int i = 0; i < 100; i++)
    {
        cout << mbi.insert(mbi.length() - 4, to_string(suffix)) << endl;
        mbi = "blade_mbi.bin";
        suffix++;
    }

    return 0;

}

// g++ -std=c++0x main.cpp
