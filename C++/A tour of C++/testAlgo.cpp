#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

template<typename T>
using Iterator = typename T::iterator;

template<typename C, typename V> 
vector<Iterator<C>> find_all(C& c, V v) 
// find all occurrences of v in c 
{ 
	vector<Iterator<C>> res; //must write typename C::iterator 
	for (auto p = c.begin(); p!=c.end(); ++p) 
		if (*p==v) 
			res.push_back(p); 
		return res; 
}

void test() 
{ 
	string m {"Mary had a little lamb"}; 
	for (auto p : find_all(m,'a')) 
	{
		if (*p != 'a') 
			cerr << "a bug!\n"; 
		cout << *p <<" ";
	}
	cout << endl;
}

int main()
{
	test();
	return 0;
}