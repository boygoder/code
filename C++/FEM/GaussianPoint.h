#ifndef _GAUSSIAN_POINT_H_
#define _GAUSSIAN_POINT_H_
#include "Point.h"
#include <fstream>
#include <string>
/**
 * @brief 高斯点基类，所有单元上的高斯点继承此类；
 * 
 */
template<unsigned int DIM>
class GaussianPoint
{
public:
    /**
     * @brief 从文件读入指定代数精度的高斯点信息；
     * 
     */
    virtual void LoadGaussianInfo(int) = 0;
    /**
     * @brief 返回指定序数的高斯点坐标信息
     * 
     * @return Point<DIM>& 点坐标
     */
    virtual Point<DIM>& GaussianPointInfo(int) = 0;
    /**
     * @brief 返回指定序数的高斯点权重信息
     * 
     * @return double 权重数值
     */
    virtual double GaussianWeightInfo(int) = 0;
    /**
     * @brief 返回高斯点个数
     * 
     * @return int 个数
     */
    virtual int GaussianPointNumInfo() = 0;
protected:
    int _Algebraic_precision;
    vector<Point<DIM>> _GaussPoint;
    vector<double> _Weight;
    int _GaussianPointNum;
};


/**
 * @brief 矩形单元上的高斯点信息类，从抽象类GaussianPoint<2>继承；
 * 
 */
class Quadrilateral_Element_GaussianInfo:public GaussianPoint<2>
{
public:
    Quadrilateral_Element_GaussianInfo(){};
    Quadrilateral_Element_GaussianInfo(int);
    virtual void  LoadGaussianInfo(int);
    virtual Point<2>& GaussianPointInfo(int);
    virtual double GaussianWeightInfo(int);
    virtual int GaussianPointNumInfo(){return _GaussianPointNum;};
};
Quadrilateral_Element_GaussianInfo::Quadrilateral_Element_GaussianInfo(int AlgPrec)
{
    LoadGaussianInfo(AlgPrec);
}
void Quadrilateral_Element_GaussianInfo::LoadGaussianInfo(int AlgPrec)
{
    std::string DocPath("GaussPntDoc/quadrilateral/");
    DocPath += std::to_string(AlgPrec);
    DocPath += ".txt";
    std::fstream fs;
    fs.open(DocPath);
    fs >> _GaussianPointNum;
    double x,y;
    for(int i = 0;i < GaussianPointNumInfo();i++)
    {
        fs >> x >> y >> _Weight[i];
        Point<2> GaussianPoint({x,y});
        _GaussPoint.push_back(GaussianPoint);
    }
}
Point<2>& Quadrilateral_Element_GaussianInfo::GaussianPointInfo(int i)
{
    return _GaussPoint[i];
}
double Quadrilateral_Element_GaussianInfo::GaussianWeightInfo(int i)
{
    return _Weight[i];
}

#else
#endif