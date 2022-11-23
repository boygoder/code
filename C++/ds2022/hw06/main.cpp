#include "Sorter.h"
#include "string"
#include <iostream>
class Node
{
public:
	int num;
	string s;
	friend bool operator<(const Node& a, const Node &b)
	{
		return (a.num < b.num);
	}
	friend ostream& operator<<(ostream& output, Node& a)
	{
		output << a.num << " " << a.s;
		return output;
	}
};

// struct 
// {
// 	bool operator()(Node& a, Node b) const
// 	{
// 		return (a.s < b.s);
// 	}	
// } NodeLess;

auto NodeLess = [](const Node& a, const Node b)
{
	return (a.s  < b.s);
};

auto NodeGreater = [](const Node& a, const Node b)
{
	return (a.num > b.num);
};


int main()
{
    vector<Node> NodeArray;
    NodeArray.push_back({1,"njy"});
    NodeArray.push_back({2,"zql"});
    NodeArray.push_back({3,"shr"});

    cout <<"InsertionSort:\n";
  	//按字符串排列，升序
  	InsertionSorter<Node,decltype(NodeLess)> s1;
    s1.sort(NodeArray,NodeLess);
    cout << "按字符串排列，升序\n";
    for(auto p : NodeArray)
    {
    	cout << p << endl;
    }
    //默认排列:按数字排列，升序
	InsertionSorter<Node> s2;
    s2.sort(NodeArray);
    cout << "按数字排列，升序\n";
    for(auto p : NodeArray)
    {
    	cout << p << endl;
    }
    //按数字排列，降序
    InsertionSorter<Node,decltype(NodeGreater)> s3;
    s3.sort(NodeArray,NodeGreater);
    cout << "按数字排列，降序\n";
    for(auto p : NodeArray)
    {
    	cout << p << endl;
    }

    cout << "MergeSort:\n";
  	//按字符串排列，升序
  	MergeSorter<Node,decltype(NodeLess)> m1;
    s1.sort(NodeArray,NodeLess);
    cout << "按字符串排列，升序\n";
    for(auto p : NodeArray)
    {
    	cout << p << endl;
    }


    MergeSorter<Node> m2;
    m2.sort(NodeArray);
    cout << "按数字排列，升序\n";
    for(auto p : NodeArray)
    {
    	cout << p << endl;
    }

    //按数字排列，降序
    MergeSorter<Node,decltype(NodeGreater)> m3;
    m3.sort(NodeArray,NodeGreater);
    cout << "按数字排列，降序\n";
    for(auto p : NodeArray)
    {
    	cout << p << endl;
    }



  	//按字符串排列，升序
  	QuickSorter<Node,decltype(NodeLess)> q1;
    q1.sort(NodeArray,NodeLess);
    cout << "按字符串排列，升序\n";
    for(auto p : NodeArray)
    {
    	cout << p << endl;
    }

   	QuickSorter<Node> q2;
    q2.sort(NodeArray);
    cout << "按数字排列，升序\n";
    for(auto p : NodeArray)
    {
    	cout << p << endl;
    }
        //按数字排列，降序
    QuickSorter<Node,decltype(NodeGreater)> q3;
    q3.sort(NodeArray,NodeGreater);
    cout << "按数字排列，降序\n";
    for(auto p : NodeArray)
    {
    	cout << p << endl;
    }
    return 0;
}