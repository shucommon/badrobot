#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int main()
{
	char pci_addr[32];
	sprintf(pci_addr, "00:%02X:%02X:%02X",1, 2, 3); 
	string str = pci_addr;
	string pci_str = "test ";
	pci_str += str;

	cout << pci_str << endl;
 
	return 0;
}

