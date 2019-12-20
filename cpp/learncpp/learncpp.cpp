#include <iostream>
#include <iomanip>

using namespace std;

void float_out()
{
    float a = 10304.31, b = 43.3, c = 5;
    //cout << setiosflags(ios::fixed);
    cout << setiosflags(ios::scientific);

    cout << setprecision(2);
    cout  << setw(8) << a << '\n';
    cout  << setw(8) << b << '\n';
    cout  << setw(8) << c << '\n';
}

void noskipws()
{
    char c;
    cin >> noskipws;
    while(cin >> c)
        cout << c;
}

//void swap(int &, int &);
inline void swap(int &, int &);
// mix c/cpp std in out need call ios::sync_with_stdio() first
int main()
{
    float_out();
    //noskipws();
    string s1;
    //s1 = "abc" + "def";   // wrong, "abc" and "def" is c style string
    string s2 = "abc", s3 = "def";
    s1 = s2 + s3;
    cout << s1;

    int i = 1, j = 2;
    swap(i, j);
    cout << i << " " << j << endl;
    return 0;
}

//inline void swap(int &a, int &b)
void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}
