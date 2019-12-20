#include <iostream>
using namespace std;

class A {
public:
    void set(int val) { a = val; }
    int get() const { return a;}
    void printxy() { cout << x << " " << y << endl; }
    A() : y(1), x(2) {}
private:
    int a;
    int x;
    int y;
};

int main()
{
    A a;
    a.set(1);
    cout << a.get() << endl;
    A b(a);
    cout << b.get() << endl;
    a.set(2);
    cout << a.get() << endl;
    cout << b.get() << endl;
    a.printxy();

    return 0;
}
    
