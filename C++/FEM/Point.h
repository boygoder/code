#ifndef _POINT_
#define _POINT_

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>


using namespace std;

void abort(int error_code)
{
    switch (error_code)
    {
    case 1:
		cout << "not matched" << endl;
		break;
    default:
		break;
    }
    exit(-1);
};

template<unsigned int DIM>
class Point
{
protected:
    double value[DIM];
public:
    Point();
    Point(const vector<double>& Point_vector);
    Point(const std::initializer_list<double>& Point_list);
    Point(const double* array);
    ~Point(){};
    double& operator[](const unsigned int d);
    template<unsigned int D>
    friend ostream& operator<<(ostream& os, const Point<D> & p);
    template<unsigned int D>
    friend double distance(const Point<D> p1, const Point<D> p2);
};

template<unsigned int DIM>
Point<DIM>::Point()  
{  
    fill(value, value + DIM, static_cast<double>(0));
};

template<unsigned int DIM>
Point<DIM>::Point(const vector<double>& p_vector)
{
    if(p_vector.size() != DIM)
    {
       abort(1);
    }
    vector<double>::const_iterator i_begin = p_vector.begin();
    vector<double>::const_iterator i_end = p_vector.end();
    copy(i_begin, i_end, value);
};
template<unsigned int DIM>
Point<DIM>::Point(const std::initializer_list<double>& Point_list)
{
    if(Point_list.size() != DIM)
    {
        throw PointDimensionException(Point_list.size(), DIM);
    }
    std::initializer_list<Real>::const_iterator i_begin = Point_list.begin();
    std::initializer_list<Real>::const_iterator i_end = Point_list.end();
    std::copy(i_begin, i_end,_value);
};

template<unsigned int DIM>
Point<DIM>::Point(const double* array)
{
    copy(array, array + DIM, value);
}

template<unsigned int DIM>
double& Point<DIM>::operator[](const unsigned int d)
{
    return value[d];
}

template<unsigned int D> ostream& operator<<(ostream& os, const Point<D> & p)
{
    os << "(";
    for(unsigned int d = 0; d < D - 1; d++)
    {
        os << p.value[d] << ", ";
    }
    os << p.value[D - 1] << ")";
    return os;
}

template<unsigned int D> double distance(const Point<D> p1, const Point<D> p2)
{
    double temp;
    for(unsigned int d = 0; d < D; d++)
        temp += (p1.value[d] - p2.value[d]) * (p1.value[d] - p2.value[d]);
    return sqrt(temp);
}


#else 
// DO NOTHING.
#endif