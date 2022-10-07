#include <iostream>
using namespace std;
int main()
{
	int *a = new int();
	double *b = new double();
	*a = 2;
	*b = 3.14;
	cout << a << " " << b;
	delete a;
	delete b;
	return 0;
}