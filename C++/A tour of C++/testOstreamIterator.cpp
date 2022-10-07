#include <ostream>
#include <string>
#include <iterator>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
using path = std::filesystem::path;
void test() {
	ostream_iterator<string> oo {cout};
	*oo = "Hello "; // equal to cout << "Hello ";
	++oo;
	*oo = "World"; 
	istream_iterator<string> ii {cin};
	istream_iterator<string> eos {}; // end of stream
}
bool copyFile(path& from, path& to) {

	
	ifstream is {from}; // input stream for file "from" 
	
	istream_iterator<string> ii {is}; // input iterator for stream 
	istream_iterator<string> eos {}; // input sentinel
	
	ofstream os {to}; // output stream for file "to" 
	ostream_iterator<string> oo {os,"\n"}; // output iterator for stream 
	
	set<string> b {ii,eos}; // b is a vector initialized from input 
	 
	unique_copy(b.begin(),b.end(),oo); // copy buffer to output, discard replicated values 
	
	return !is.eof() || !os; // return error state (§1.2.1, §10.4)
}
int main()
{
	path from = "./from.txt";
	path to = "./to.txt";
	if (copyFile(from,to))
		cerr << "eof || os ";
	return 0;
}