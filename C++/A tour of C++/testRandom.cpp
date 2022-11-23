#include <random>
#include <iostream>
using namespace std;
int main()
{
	std::random_device r;
    std::default_random_engine re(r()); // the default engine 
	std::uniform_int_distribution<int> uniform_dist{2,6}; // distribution that maps to the ints 1..6 
	for(int i = 0; i < 10; ++i)
	{
		int x = uniform_dist(re);
		cout << x << " ";
	}
	return 0;
}