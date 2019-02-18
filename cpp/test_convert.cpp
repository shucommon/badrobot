#include <iostream>
#include <string>
using namespace std;

typedef struct test
{
	int e;
	char a;
	char b;
	char c;
	char d;
} test_t;

int main()
{
	//string str = "abcdefgh";
	char str[] = "abcd";
	test_t *tt = (test_t *)malloc(sizeof(test_t));
	void * addr = tt;
	memset(tt, 'x', sizeof(test_t));
	tt = (test_t *)str;
	cout << "sizeof(test_t) = " << sizeof(test_t) << ", str len = " << strlen(str) << endl;
	cout << "str " << str << "; tt:" << hex << tt->e << " " << tt->a << " " << tt->b << " " << tt->c << " " << tt->d << endl;
	free(addr);
	return 0;
}
