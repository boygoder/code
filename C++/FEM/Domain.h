#ifndef _DOMAIN_
#define _DOMAIN_

#include "Point.h"
#include "assert.h"

template <unsigned int DIM>
class Domain
{
public:
    Domain() = default;
    virtual ~Domain() = default;
    Domain(std::vector<Point<DIM>>& pointList) : _PointList{pointList} {};
    virtual Point<DIM>& GetPoint(int _i)
    {
        return _PointList[_i];
    };
protected: 
    std::vector<Point<DIM>> _PointList;
};

/** 
 *@brief 二维矩形
 */
class Rectangle2D: public Domain<2>
{
public:
    //逆时针顺序
    Rectangle2D(std::vector<Point<2>>& pointList)
    {
        assert(pointList.size() == 4);
        copy(pointList.begin(),pointList.end(),_PointList);
    };
    virtual Point<2>& GetPoint(int _i)
    {
        return _PointList[_i];
    };
};

#else
#endif
