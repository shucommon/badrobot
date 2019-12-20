#include <iostream>
using namespace std;

class intArray {
public:
    int& operator[](int);
    const int& operator[](int) const;
    intArray(int s);
    int get_size() const { return size; }
private:
    int size;
    int *a;
    int c;
};

int& intArray::operator[](int i) {
    if(i < 0 || i >= size)
        throw string("OutOfBounds");
    return a[i];
}

const int& intArray::operator[](int i) const {
    if(i < 0 || i >= size)
        throw string("OutOfBounds");
    return a[i];
}

intArray::intArray(int s) {
    try {
        a = new int[s];
    }
    catch (bad_alloc) {
        cerr << "Unable to allocate storage for intArray\n";
        throw;
    }
    size = s;
    c = 2;
}

int main()
{
    intArray b(5);
    int i;
    try {
        for(i = 0; i < b.get_size(); i++)
            b[i] = 2 * i;
        for(i = 0; i < 6; i++)
            cout << b[i] << '\n';
    }
    catch (string &s) {
        cerr << s << '\n';
        cerr << "i = " << i << '\n';
    }
    return 0;
}
