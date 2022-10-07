#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void f(const vector<double>& v, double* res)
{

};
struct F
{
public:
	F(const vector<double>& vv, double* p):v(vv),res(p){};
	void operator()(){};
private:
	const vector<double>& v;
	double* res;

};

double g(const vector<double>&)
{
	return 1.0;
}; // use return value

void user(vector<double>& vec1, vector<double> vec2, vector<double> vec3) { 
	double res1; 
	double res2; 
	double res3;
	
	thread t1 {f,cref(vec1),&res1}; // f(vec1,&res1) executes in a separate thread 
	thread t2 {F{vec2,&res2}}; // F{vec2,&res2}() executes in a separate thread 
	thread t3 { [&](){ res3 = g(vec3); } }; // capture local variables by reference 

	t1.join(); 
	t2.join(); 
	t3.join(); 
	cout << res1 << ' ' << res2 << ' ' << res3 << '\n'; 

};

int main()
{
	vector<double> v1(10,0);
	vector<double> v2(10,1);
	vector<double> v3(10);
	user(v1,v2,v3);
	return 0;
};