#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>


using namespace std;

int main(int argc, char** argv)
{
    int a;
    string str = "03 01 00 01 00 02 00 fc";
    stringstream stream(str);
    cout << "stream: " << stream.str() << endl;
    vector<int> val;
    while(stream >> hex >> a)
    {
        cout << a << " ";
        val.push_back(a);
    }

    for( std::vector<int>::const_iterator i = val.begin(); i != val.end(); ++i)
        std::cerr << *i << ' ';
    cout << "size " << val.size() << endl;


    return 0;
}
