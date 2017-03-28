#include <iostream> 
#include <stdlib.h>
#include <set> 
#define id_Grace 40000
using namespace std; 
typedef set<int> ISET; 
ISET GetPridePersonId(const int num, const int pride_num) 
{   
  int id; 
  ISET iset;   
  while (1) { 
     id = (int)((double)rand() / RAND_MAX * num) % (num - 1); 
     if ( iset.find(id) == iset.end() ||
		  id == id_Grace )
	 { 
       iset.insert(id); 
     } 
     if (iset.size() >= pride_num) { 
       break; 
     }      
   }    
   return iset; 
} 
void print(ISET &iset) 
{ 
  ISET::iterator iter; 
  cout<<"item as :\n"; 
  for (iter = iset.begin(); iter != iset.end(); ++ iter) { 
    cout<<*iter<<"\n"; 
  } 
} 
int main(int argc, char **argv)  
{ 
  const int total_person = 300000; 
  const int total_pride_person = 100; 
  ISET iset = GetPridePersonId(total_person, total_pride_person); 
  print(iset); 
  return 0; 
}

