#include <thread>
#include <vector>
#include <future>
#include <numeric>
#include <iostream>
using namespace std;

double accum(double* beg, double* end, double init) 
// compute the sum of [beg:end) starting with the initial value init 
{ 
	return accumulate(beg,end,init); 
};



double comp2(vector<double>& v) 
{ 
	using Task_type = double(double*,double*,double); 
	// type of task 
	packaged_task<Task_type> pt0 {accum}; 
	// package the task (i.e., accum) 
	packaged_task<Task_type> pt1 {accum}; 
	future<double> f0 {pt0.get_future()}; 
	// get hold of pt0’s future 
	future<double> f1 {pt1.get_future()}; 
	// get hold of pt1’s future 
	double* first = &v[0]; 
	thread t1 {move(pt0),first,first+v.size()/2,0}; 
	// start a thread for pt0 
	thread t2 {move(pt1),first+v.size()/2,first+v.size(),0}; 
	// start a thread for pt1 
	// ... 
	t1.join();
	t2.join();
	return f0.get()+f1.get(); // get the results 
}

double comp4(vector<double>& v) 
// spawn many tasks if v is large enough 
{ 
	if (v.size()<10000) // is it worth using concurrency? 
		return accumulate(v.begin(),v.end(),0.0); 
	double* v0 = &v[0]; 

	auto sz = v.size(); 
	auto f0 = async(accum,v0,v0+sz/4,0.0); // first quarter 
	auto f1 = async(accum,v0+sz/4,v0+sz/2,0.0); // second quarter 
	auto f2 = async(accum,v0+sz/2,v0+sz*3/4,0.0); // third quarter 
	auto f3 = async(accum,v0+sz*3/4,v0+sz,0.0); // fourth quarter

	return f0.get()+f1.get()+f2.get()+f3.get(); // collect and combine the results 
}

int main()
{
	vector<double> v{1.0,2.0,3.0,4.0};
	double res = comp4(v);
	cout << res << endl;
	return 0;
};