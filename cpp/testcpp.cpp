#include <iostream>
using namespace std;

class base
{
public:
    int a;
    int b;
    int funa()
    {
        cout << a << " " << b << endl;
    }
};

class child: public base
{
public:
    int funb()
    {
        cout << b << " " << a << endl;
    }
};

int main()
{
    base bs;
    bs.a = 1;
    bs.b = 2;

    child *ch = NULL; 
    ch = &bs;
    ch->funa(); 
    ch->funb();

    return 0;
}
