#include "HeapSort.h"
#include "Quicksort.h"
#include <random>
#include <chrono>
#include <cassert>
#include <iostream>
#include <fstream>
#include <math.h>
#include <unordered_map>
using namespace std::chrono;
enum class Sorter {heapsort,quicksort};
vector<int> generateVector(int len, double proportion)
{
	assert(proportion >=0 && proportion <= 1);
	int c = sqrt(len*(len-1)*(1 - proportion));
	int orderedLen = c;
	vector<int> vec;
	for (int i = 0; i < orderedLen; i++)
	{
		vec.push_back(len - i);
	}
	for(int i = orderedLen; i < len; i++)
	{
		vec.push_back(len + i);
	}
	// random_device r;//Seed with a real random value, if available
 	// default_random_engine re(r()); // the default engine
	// uniform_int_distribution<int> uniform_dist{0,len}; // distribution that maps to the ints
	// for (int j = 0; j < len; j++)
	// {
	// 	vec.push_back(uniform_dist(re));
	// }

	// for(auto p : vec)
	// {
	// 	cout << p <<" ";
	// }
	return vec;
}

double getRunTime(vector<int>& array, int loops, Sorter sorter)
{

	double Time = 0.0;
	for(int i = 1; i <= loops; ++i)
	{	
		auto w0 = std::chrono::high_resolution_clock::now();
		switch(sorter)
		{
			case Sorter::heapsort:
			{
				heapsort(array);
				break;
			}
			case Sorter::quicksort:
			{
				quicksort(array);
				break;
			}
			default:
				break;
		}
		auto w1 = std::chrono::high_resolution_clock::now();
				
		double time = duration_cast<milliseconds>(w1- w0).count();
		//cout << "Time = " << scientific << time << "msec\n";
		Time += time;
	}
	return Time;
}

int main()
{
	vector<int> sizes = {100000};//,20000,40000,80000,160000};
	int loops = 20;
	vector<double> proportion = {0.01,0.1,0.9,0.99};
	ofstream fout("data.txt",ios::out);     //创建一个data.txt的文件

	for(auto p : proportion)
	{
		unordered_map<int,double> quickRunTime;
		unordered_map<int,double> heapRunTime;
		fout << "Proportion = "<< p << endl;
		for (auto size : sizes)
		{
			vector<int> v1 = generateVector(size,p);
			vector<int> v2 = v1;

			double quickTime = getRunTime(v1,loops,Sorter::quicksort);
			quickRunTime.insert({size,quickTime});
			cout << "QuickSort,"  << defaultfloat << p << ", Time = "  << quickTime << "msec\n";

			double heapTime = getRunTime(v2,loops,Sorter::heapsort);
			heapRunTime.insert({size,heapTime});
			cout << "HeapSort,"  << defaultfloat << p << ", Time = "  << heapTime << "msec\n";
			
		}
		fout << "QuickSort" << endl;
		for(auto &p : quickRunTime)
		{
			fout << p.first << ", " << p.second << endl;
		}	
		fout << "HeapSort" << endl;
		for(auto &p : heapRunTime)
		{
			fout << p.first << ", " << p.second << endl;
		}			
	}
	fout.close();
	return 0;
}