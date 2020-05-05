#include <iostream>
using namespace std;

class C {
    public:
        C();
        C( C& obj);
        //C( C obj);  // copy_constructor.cpp:8:14: error: copy constructor must pass its first argument by reference
        C( C obj, int b);

        int a;
};

C::C()
{
    a = 0;
    cout << "from default constructor, a = " << a << endl;
}

C::C(C& obj)
{
    cout << "form defualt copy constructor, a = " << a << endl; 
    a = obj.a;
}

C::C(C obj, int b)
{
    a = b;
    cout << "form copy constructor, a = " << a << endl; 
}

int main()
{
    cout << "define c" << endl;
    C c;
    int b = 1;
    cout << "call cc" << endl;
    C cc(c, b);
    
    return 0;
}
