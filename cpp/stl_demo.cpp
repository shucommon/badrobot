#include<iostream>
#include<vector>
#include<list>
#include<deque>
#include<algorithm>
#include<iterator>
#include<stack>
#include<string>

#include<map>
#include<set>

using namespace std;

void show(int a)
{
    cout << a << " ";
}

bool cmp(int a, int b)
{
    return a < b;
}
bool rcmp(int a, int b)
{
    return a > b;
}

void list_demo()
{
    list<int> lst;
    lst.push_front(1);  // push in front
    lst.push_back(2);  // push in end 
    for(auto t : lst) {
        cout << t << " ";
    }
    lst.pop_front();
    lst.pop_back();
    for(auto t : lst) {
        cout << t << " ";
    }

    list<int> one(5, 2);    // list of 5 2s
    int stuff[5] = {1, 2, 4, 8, 6};
    list<int> two;
    two.insert(two.begin(), stuff, stuff + 5);
    int more[6] = {6, 4, 2, 4, 6, 5};
    list<int> three(two);
    three.insert(three.end(), more, more + 6);

    std::cout << "list one: ";
    std::for_each(one.begin(), one.end(), show);
    std::cout << endl << "list two: ";
    std::for_each(two.begin(), two.end(), show);
    std::cout << endl << "list three: ";
    std::for_each(three.begin(), three.end(), show);
    three.remove(2);
    cout << endl << "list three minus 2s: ";
    std::for_each(three.begin(), three.end(), show);
    three.splice(three.begin(), one);       // move one into three, before begin pos
    cout << endl << "list three after splice: ";
    std::for_each(three.begin(), three.end(), show);
    cout << endl << "list one: ";
    std::for_each(one.begin(), one.end(), show);
    three.unique(); // delete dumplicated one 连续的
    cout << endl << "list three after unique: ";
    std::for_each(three.begin(), three.end(), show);
    three.sort();
    three.unique();
    cout << endl << "list three after sort&unique: ";
    std::for_each(three.begin(), three.end(), show);
    two.sort();
    three.merge(two);       // must sort before merge
    cout << endl << "sorted two merged into three: ";
    std::for_each(three.begin(), three.end(), show);
    cout << endl;
}

void deque_demo()
{
    deque<int> dq;
    dq.push_front(1);
    dq.push_back(2);
    for(auto t : dq) {
        cout << t << " ";
    }
    //cout << dq.pop_back();
    dq.pop_front();
    for(auto t : dq) {
        cout << t << " ";
    }
}

void stack_demo()
{
    stack<int> stk;
    stk.empty();
    stk.size();
    stk.push(1);
    stk.pop();
    stk.top();  // return top element
}

void map_demo()
{
    map<string, int> mapOfWords;
    mapOfWords.insert(make_pair("earth", 1));
    mapOfWords.insert(make_pair("moon", 2));
    mapOfWords["sun"] = 3;
    mapOfWords["earth"] = 3;

    map<string, int>::iterator it = mapOfWords.begin();
    while(it != mapOfWords.end()) {
        cout << it->first << " :: " << it->second << endl;
        it++;
    }

    // Check if insertion is successful or not
    if(mapOfWords.insert(make_pair("earth", 1)).second == false) {
        cout << "Element whth key 'earth' not inserted because already existed" << endl;
    }

    // Searching element in std::map by key.
    if(mapOfWords.find("sun") != mapOfWords.end()) {
        cout << "word 'sun' found" << endl;
    }
    if(mapOfWords.find("mars") == mapOfWords.end()) {
        cout << "word 'mars' not found" << endl;
    }

    auto itm = mapOfWords.find("moon");
    cout << "it " << itm->first << " :: " << itm->second << endl;
    
    // Erasing By iterator
    std::map<std::string, int>::iterator itd = mapOfWords.find("moon");
    mapOfWords.erase(itd);
 
    // Erasing By Key
    mapOfWords.erase("earth");

    // Iterate over a map using std::for_each and Lambda function
    for_each(mapOfWords.begin(), mapOfWords.end(),
                [](pair<string, int> element) {
                    string word = element.first;
                    int count = element.second;
                    cout << word << " :: " << count << endl;
                }
    );
    mapOfWords.size();
    mapOfWords.empty();
    mapOfWords.clear();
}

void vector_demo()
{
    // old ways
    size_t size = 10;
    int sarray[10];
    int *darray = new int[size];
    for(int i = 0; i < 10; i++) {
        sarray[i] = i;
        darray[i] = i;
    }
    delete[] darray;

    // vector way
    vector<int> array;
    array.reserve(10);    // make room for 10 elements
    //vector<int> array(size);    // make room for 10 integers,

    array.resize(3);          // at this point, the vector contains
    array.resize(6, 1);       // resize again, fill up with ones
    array.push_back(1);
    array.push_back(2);
    cout << array.at(0) << endl;
    for(auto ele : array) {
        cout << ele << endl;
    }
    for(vector<int>::iterator it = array.begin(); it != array.end(); it++) {
        cout << *it << endl;
    }
    // delete 0,1 element
    array.erase(array.begin(), array.begin() + 2);

    vector<int> old_v;
    vector<int> new_v;
    old_v.push_back(1);
    old_v.push_back(2);
    new_v.push_back(3);
    new_v.push_back(4);

    vector<int> v_back(old_v);  // copy constructor used
    old_v.swap(v_back); // swap v_back with old_v

    // insert befor old_v.begin()
    old_v.insert(old_v.begin(), new_v.begin(), new_v.end());
    old_v.insert(old_v.begin() + 1, 5);
    for(auto ele: old_v) {
        cout << ele << " ";
    }
    cout << endl;

    for_each(old_v.begin(), old_v.end(), show);
    copy(old_v.begin(), old_v.end(), ostream_iterator<int>(cout, " "));

    sort(old_v.begin(), old_v.end(), cmp);
    copy(old_v.begin(), old_v.end(), ostream_iterator<int>(cout, " "));

    sort(old_v.rbegin(), old_v.rend(), cmp);
    copy(old_v.begin(), old_v.end(), ostream_iterator<int>(cout, " "));

    sort(old_v.begin(), old_v.end(), rcmp);
    copy(old_v.begin(), old_v.end(), ostream_iterator<int>(cout, " "));

    cout << endl;
    cout << old_v.front() << endl;
    cout << old_v.back() << endl;
}

void set_demo()
{
	std::set<std::string> setOfNumbers;
 
	// Lets insert four elements
	setOfNumbers.insert("first");
	setOfNumbers.insert("second");
	setOfNumbers.insert("third");
	setOfNumbers.insert("first");
 
	// Only 3 elements will be inserted
	std::cout<<"Set Size = "<<setOfNumbers.size()<<std::endl;
 
	// Iterate through all the elements in a set and display the value.
	for (std::set<std::string>::iterator it=setOfNumbers.begin(); it!=setOfNumbers.end(); ++it)
	    std::cout << ' ' << *it;
	std::cout<<"\n";

    // Search for element in set using find member function
	std::set<std::string>::iterator it = setOfNumbers.find("second");
	if(it != setOfNumbers.end())
		std::cout<<"'first'  found"<<std::endl;
	else
		std::cout<<"'first' not found"<<std::endl;
 
	// Search for element in set using find member function
	it = setOfNumbers.find("fourth");
	if(it != setOfNumbers.end())
		std::cout<<"'fourth'  found"<<std::endl;
	else
		std::cout<<"'fourth' not found"<<std::endl;

    // insert check
    if(setOfNumbers.insert("first").second)
        std::cout<<" inserted sucessfuly\n";
    else
        std::cout<<"element was already present in set\n";

    // earse
    setOfNumbers.erase("third");

	set<int> s;
	s.insert(1);
	s.insert(2);
	s.insert(3);
	s.insert(1);
	cout<<"set 的 size 值为 ："<<s.size()<<endl;
	cout<<"set 的 maxsize的值为 ："<<s.max_size()<<endl;
	cout<<"set 中的第一个元素是 ："<<*s.begin()<<endl;
	cout<<"set 中的最后一个元素是:"<<*s.rbegin()<<endl;
	s.clear();
	if(s.empty())
	{
		cout<<"set 为空 ！！！"<<endl;
	}
	cout<<"set 的 size 值为 ："<<s.size()<<endl;

    set<pair<int, int>> ss;
    ss.insert(pair<int, int>(1, 2));
    ss.insert(pair<int, int>(3, 4));
    cout << (*ss.begin()).first << endl;;
    cout << (*ss.begin()).second<< endl;;
}

void string_demo()
{
    char *line = "short line for testing";
    
    // with no arguments
    string s1;
    s1 = "Anatoliy";
    cout << "s1  is: " << s1 << endl;

    // copy constructor
    string s2 (s1);
    cout << "s2  is: " << s2 << endl;

    // one argumen
    string s3 (line);
    cout << "s3  is: " << s3 << endl;

    // first argumen C string
    // second number of characters
    string s4 (line,10);
    cout << "s4  is: " << s4 << endl;

    // 1 - C++ string
    // 2 - start position
    // 3 - number of characters
    string s5 (s3,6,4); // copy word 'line' from s3
    cout << "s5  is: " << s5 << endl;

    // 1 - number characters
    // 2 - character itself
    string s6 (15,'*');
    cout << "s6  is: " << s6 << endl;

    // 1 - start iterator
    // 2 - end iterator
    string s7 (s3.begin(),s3.end()-5);
    cout << "s7  is: " << s7 << endl;

    // you can instantiate string with assignment
    string s8 = "Anatoliy";
    cout << "s8  is: " << s8 << endl;

    cout << "len " << s8.length() << " size " << s8.size() << endl;

    string str = "Nobody is perfect";
    string s = "";
    char *ch   = "abcdef";
    s.append(str, 0, 6);
    cout << s << endl;

    string::iterator inpIt1 = str.begin()+6;
                    //start from ' is'
    string::iterator inpIt2 = str.end();

    s.append(inpIt1,inpIt2);
    cout << "s is : " << s << endl;
    // appends three !
    s.append(3,'!');
    cout << "s is : " << s << endl;
    s.append(ch,3);
    cout << "s is : " << s << endl;

    s.assign(str);
    cout << "s is : " << s << endl;
    s.assign(str,10,7); // perfect
    cout << "s is : " << s << endl;
    s.assign(ch,6);
    cout << "s is : " << s << endl;
    s.assign(ch);
    cout << "s is : " << s << endl;
    s.assign(str.begin(),str.end());
    cout << "s is : " << s << endl;
    s.assign(17,'*');
    cout << "s is : " << s << endl;

    // Returns s[pos]
    for ( int pos = 0; pos < s.length(); ++pos )
    	cout << s.at(pos) << " ";
    cout << endl;
    string::iterator It = s.begin();

    char *ary = new char[s.length()+1];
    // strcpy ( ary, str ); that is wrong way
    strcpy ( ary, s.c_str() ); // that is correct

    s = "hello";
    s.erase(0, 2);
    cout << "s is : " << s << endl;
    s.replace(1, 2, "LO");
    cout << "s is : " << s << endl;


    string str1 = "We go step by step to the target";
    cout << "str is: " << str1 << endl;
    int n = str1.find("step");
    string ss = str1.substr(n);
    cout << "s   is: " << ss << endl;
    ss = str1.substr(n,12);
    cout << "s   is: " << ss << endl;

    /*
    string (1)	
    string& insert (size_t pos, const string& str);

    substring (2)	
    string& insert (size_t pos, const string& str, size_t subpos, size_t sublen);

    c-string (3)	
    string& insert (size_t pos, const char* s);

    buffer (4)	
    string& insert (size_t pos, const char* s, size_t n);

    fill (5)	
    string& insert (size_t pos, size_t n, char c);
        void insert (iterator p, size_t n, char c);

    single character (6)	
    iterator insert (iterator p, char c);

    range (7)	
    template <class InputIterator>
    void insert (iterator p, InputIterator first, InputIterator last);
   */
}

void multimap_demo() {
    cout << endl << "test multimap" << endl;
    multimap<int, int> mmp;
    mmp.insert(pair<int, int>(1, 1));
    mmp.insert(pair<int, int>(1, 2));
    mmp.insert(pair<int, int>(3, 3));
    mmp.insert(pair<int, int>(3, 4));
    auto it = mmp.find(1);
    auto n = mmp.count(1);
    for(int i = 0; i < n; i++) {
        cout << it->second << " ";
        it++;
    }
    cout << endl;
    auto iit = mmp.find(3);
    auto nn = mmp.count(3);
    for(int i = 0; i < nn; i++) {
        cout << iit->second << " ";
        iit++;
    }
    cout << endl;
}

void multiset_demo() {
}

int main()
{
    vector_demo();
    deque_demo();
    list_demo();
    map_demo();
    set_demo();
    string_demo();

    return 0;
}