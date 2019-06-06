#include <iostream>
using namespace std;

class base
{
    public:
        int a;
    protected:
        int b;
    private:
        int c;
};

class A : public base
{
    public:
        A();
        void p();
};

A::A()
{
    b = 1;  
}

void A::p()
{
    cout << b << endl;  
}


int main(void)
{
    A a;
    a.p();    
    return 0;
}
