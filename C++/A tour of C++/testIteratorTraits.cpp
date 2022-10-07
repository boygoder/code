#include <iterator>
#include <vector>
#include <forward_list>
#include <string>
#include <iostream>
#include <algorithm>
#include <concepts>
#include <ranges>
#include <iterator>
using namespace std;

template<typename C> 
using Value_type = typename C::value_type; // C’s value type
template<typename C> 
using Iterator_type = typename C::iterator; // C’s iterator type
template<typename Iter> 
using Iterator_category = typename std::iterator_traits<Iter>::iterator_category; // Iter’s category

template<typename Ran> // for random-access iterators 
void sort_helper(Ran beg, Ran end, random_access_iterator_tag) // we can subscript into [beg:end) 
{ 
	sort(beg,end); // just sort it 
}

template<typename For> // for forward iterators 
void sort_helper(For beg, For end, forward_iterator_tag) // we can traverse [beg:end) 
{
	vector<Value_type<For>> v {beg,end}; // initialize a vector from [beg:end) 
	sort(v.begin(),v.end()); // use the random access sort 
	copy(v.begin(),v.end(),beg); // copy the elements back 
}

template<typename C> 
void sort(C& c) 
{ 
	using Iter = Iterator_type<C>;
	sort_helper(c.begin(),c.end(),Iterator_category<Iter>{}); 
}

//concepts version of sort()
template<typename T> 
concept RandomAccessIterator = is_same_v<Iterator_category<T>,random_access_iterator_tag>;
template<typename T>
concept ForwardIterator = is_same_v<Iterator_category<T>,forward_iterator_tag>;

template<RandomAccessIterator Iter> 
void sortHelper2(Iter p, Iter q)
{
	sort(p,q);
}; // use for std::vector and other types supporting random access 

template<ForwardIterator Iter> 
void sortHelper2(Iter p, Iter q) // use for std::list and other types supporting just forward traversal 
{ 
	vector<Value_type<Iter>> v{p,q}; 
	sort(v); // use the random-access sort 
	copy(v.begin(),v.end(),p); 
}


template<ranges::range R>
void sort2(R& r) 
{ 
	sortHelper2(r.begin(),r.end()); // use the appropriate sort 
}



void test(vector<string>& v, forward_list<int>& lst)
{ 
	sort2(v); // sort the vector 
	sort2(lst); // sort the singly-linked list 
}


int main()
{
	std::vector<string> v{"Hello","World","!"};
	forward_list<int> f{1,4,34,56,3,35};
	test(v,f);
	for(string& s:v) {
		cout << s << " ";
	}
	cout <<endl;
	for(int& i:f) {
		cout << i << " ";
	}
}