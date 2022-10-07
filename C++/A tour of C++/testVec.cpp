#include <vector>
#include <iostream>
#include <exception>
using namespace std;
struct Entry { string name; int number; };

ostream& operator<<(ostream& os, const Entry& e) 
{ 
	return os << "{\"" << e.name << "\", " << e.number << "}"; 
};

void print_book(const vector<Entry>& book) 
{ 	
	for (int i = 0; i!=book.size(); ++i) 
		cout << book[i] << '\n'; 
}

int main() 
try{ 
	// your code 
} 
catch (out_of_range&) 
{
	cerr << "range error\n"; 
} 
catch (...) 
{ 
	cerr << "unknown exception thrown\n"; 
};