#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char*argv[])
{
	// check parameter counts
	if(argc != 3)
	{
		cout << "please input two parameters: app_name file1 file2" << endl;
		return -1;
	}
	
	// open the two input files
	ifstream f1, f2;

	f1.open(string(argv[1]));
	if(!f1.is_open())
	{
		cout << "Open file " << argv[1] << " failed" << endl;
		return -1;
	}

	f2.open(string(argv[2]));
	if(!f2.is_open())
	{
		cout << "Open file " << argv[2] << " failed" << endl;
		return -1;
	}
	
	// diff position
	int count = 0;
	string str1, str2; 

	while((f1 >> str1) && (f2 >> str2))
	{
		count++;
		
		// if different, output result
		if(str1.compare(str2) != 0)
		{
			cout << count << " " << str1 << " " << str2 << endl;
		}	
	}

	return 0;
}
