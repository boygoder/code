#ifndef _template<unsigned int>_TemplateElement_
#define _template<unsigned int>_TemplateElement_

#include "Dofs.h"
#include "GaussianPoint.h"
/**
 * @brief  建立一个标准单元
 */
template<unsigned int DIM>
class TemplateElement
{
public:
    /**
     * @brief Construct a new TemplateElement object
     * 
     */
    TemplateElement();
    /**
     * @brief Destroy the TemplateElement object
     * 
     */
    ~TemplateElement();

    /**
     * @brief Get the Dofs List object
     * 
     * @param i 指定序号；
     * @return Dofs<DIM>&　自由度的引用 
     */
    virtual Dofs<DIM>& GetDofsList(int i) = 0 ;
    /**
     * @brief 返回本单元里第ｉ个自由度对应的全局编号；
     * 
     * @param i 指定序号；
     * @return int 全局编号；
     */
    virtual int GetGlobalIndex(int i)  = 0 ;
    /**
     * @brief 返回本单元对应第i个高斯点坐标信息；
     * 
     * @param i 指定序号
     * @return Point<DIM>& 高斯点
     */
    virtual Point<DIM>& GaussionPoint(int i) = 0 ;
    /**
     * @brief 返回本单元对应第i个高斯点权重信息；
     * 
     * @param i 指定序号
     * @return double 高斯点对应权重的数值；
     */
    virtual double GaussionWeight(int i) = 0 ;
    /**
     * @brief 该类型单元对应的基函数；
     * 
     * @param xi 坐标１
     * @param eta 坐标２
     * @param i　基函数序数
     * @return double 该基函数的值；
     */
    virtual double phi(double xi, double eta, int i)= 0 ;
    /**
     * @brief 该类型单元对应的基函数对xi的偏导数；
     * 
     * @param xi 坐标１
     * @param eta 坐标２
     * @param i 序数
     * @return double 该偏导数的值
     */
    virtual double phi_xi(double xi, double eta, int i)  = 0;
    /**
     * @brief 该类型单元对应的基函数对eta的偏导数；
     * 
     * @param xi 坐标１
     * @param eta 坐标２
     * @param i 序数
     * @return double 该偏导数的值
     */
    virtual double phi_eta(double xi, double eta, int i)  = 0;
    /**
     * @brief 任意单元到该模板单元仿射变换对应的雅克比矩阵行列式在(xi,eta)处的值；
     * 
     * @param xi 坐标１
     * @param eta 坐标２
     * @return double 值
     */
    virtual double det_Jacobi(double xi, double eta) = 0 ;
    /**
     * @brief 基函数对x的偏导数；
     * 
     * @param xi 坐标１
     * @param eta 坐标２
     * @param i 序数
     * @return double 值
     */
    virtual double phi_x(double xi, double eta, int i)  = 0 ;
    /**
     * @brief 基函数对y的偏导数；
     * 
     * @param xi 坐标１
     * @param eta 坐标２
     * @param i 序数
     * @return double 值
     */
    virtual double phi_y(double xi, double eta, int i)  = 0 ;
    /**
     * @brief 计算并返回第ｉ个基函数在xi，eta点处的梯度向量；
     * 
     * @param xi 
     * @param eta 
     * @param i 
     * @return std::vector<double> 梯度向量；
     */
    virtual std::vector<double> gradient(double xi,double eta,int i) = 0;
    /**
     * @brief 标准单元中的点在真实单元的x坐标
     * 
     * @param xi 坐标１
     * @param eta 坐标2
     * @return double 值
     */
    virtual double Global_x(double xi, double eta)  = 0 ;
    /**
     * @brief 标准单元中的点在真实单元的y坐标
     * 
     * @param xi 坐标１
     * @param eta 坐标2
     * @return double 值
     */
    virtual double Global_y(double xi, double eta)  = 0;
    /**
     * @brief 该单元自由度个数；
     * 
     * @return int 
     */
    virtual int n_Dofs() = 0;
    /**
     * @brief 高斯点个数；
     * 
     * @return int 
     */
    virtual int n_GaussPnt() = 0;
    /**
     * @brief 计算并返回该单元的面积或体积；
     * 
     * @return double 
     */
    virtual double volume() = 0;
    /**
     * @brief 获取_grid的自由度等信息 
     * 
     */
    virtual void reinit(Grid<DIM>& _grid) = 0;
    protected:
    virtual double xi_x(double xi, double eta)  = 0;
    virtual double xi_y(double xi, double eta)  = 0 ;
    virtual double eta_x(double xi, double eta)  = 0 ;
    virtual double eta_y(double xi, double eta) = 0 ;
    
};
template <unsigned int Dim>
TemplateElement<Dim>::TemplateElement()
{
}
template<unsigned int Dim>
TemplateElement<Dim>::~TemplateElement()
{
}


class Quadrilateral_1_Element:public TemplateElement<2>
{
    typedef std::vector<Dofs<2> > DofsList;
    typedef int DofsNum;
public:
    Quadrilateral_1_Element();
    ~Quadrilateral_1_Element();
    virtual Dofs<2>& GetDofsList(int i);
    virtual int GetGlobalIndex(int i) ; 
    virtual Point<2>& GaussionPoint(int i){return _GaussInfo.GaussianPointInfo(i);};
    virtual double GaussionWeight(int i){return _GaussInfo.GaussianWeightInfo(i);};               
    virtual double phi(double xi, double eta, int i);
    virtual double phi_xi(double xi, double eta, int i)  ;
    virtual double phi_eta(double xi, double eta, int i)  ;
    virtual double det_Jacobi(double xi, double eta)   ;
    virtual double xi_x(double xi, double eta)  ;
    virtual double xi_y(double xi, double eta)   ;
    virtual double eta_x(double xi, double eta)   ;
    virtual double eta_y(double xi, double eta)   ;
    virtual double phi_x(double xi, double eta, int i)  ;
    virtual double phi_y(double xi, double eta, int i)  ;
    virtual std::vector<double> gradient(double xi,double eta,int i) ;
    virtual double Global_x(double xi, double eta);
    virtual double Global_y(double xi, double eta);
    virtual double volume(){return 4 * det_Jacobi(0,0);};
    virtual int n_Dofs(){return 4;};
    virtual int n_GaussPnt(){return _GaussInfo.GaussianPointNumInfo();};
    virtual void reinit(Grid<2>& _grid);
private:
    std::vector<Dofs<2> > _dofslist;
    Quadrilateral_Element_GaussianInfo _GaussInfo;
};

Quadrilateral_1_Element::Quadrilateral_1_Element()
{
    _dofslist.resize(4);
    
};

Dofs<2>& Quadrilateral_1_Element::GetDofsList(int i)
{
    return _dofslist[i];
}
double Quadrilateral_1_Element::phi(double xi, double eta, int i)
{
    switch(i)
    {
    case 1:
	    return (xi-1)*(eta-1)/4.0;
    case 2:
	    return -(xi+1)*(eta-1)/4.0;
    case 3:
	    return (xi+1)*(eta+1)/4.0;
    case 4:
	    return -(xi-1)*(eta+1)/4.0;
    }
    return 0;
}

double Quadrilateral_1_Element::phi_xi(double xi, double eta, int i) 
{
    switch(i)
    {
    case 1:
	    return (eta-1)/4.0;
    case 2:
	    return -(eta-1)/4.0;
    case 3:
	    return (eta+1)/4.0;
    case 4:
	    return -(eta+1)/4.0;
    }
    return 0;
}

double Quadrilateral_1_Element::phi_eta(double xi, double eta, int i) 
{
    switch(i)
    {
    case 1:
	    return (xi-1)/4.0;
    case 2:
	    return -(xi+1)/4.0;
    case 3:
	    return (xi+1)/4.0;
    case 4:
	    return -(xi-1)/4.0;
    }
    return 0;
}

double Quadrilateral_1_Element::det_Jacobi(double xi, double eta) 
{
    double J11 = 0;
    double J12 = 0;
    double J21 = 0;
    double J22 = 0;
    for (int i = 1; i <= 4; i++)
    {
        J11 = J11 + _dofslist[i-1][0]*phi_xi(xi, eta, i);
        J12 = J12 + _dofslist[i-1][1]*phi_xi(xi, eta, i);
        J21 = J21 + _dofslist[i-1][0]*phi_eta(xi, eta, i);
        J22 = J22 + _dofslist[i-1][1]*phi_eta(xi, eta, i);
    }
    return (J11*J22 - J12*J21);
}

double Quadrilateral_1_Element::xi_x(double xi, double eta)
{
    double a = 0;
    for (int i = 1; i <= 4; i++)
	    a = a + _dofslist[i-1][1]*phi_eta(xi, eta, i);
    return a / det_Jacobi(xi, eta);
}

double Quadrilateral_1_Element::xi_y(double xi, double eta)
{
    double a = 0;
    for (int i = 1; i <= 4; i++)
	    a = a + _dofslist[i-1][0]*phi_eta(xi, eta, i);
    return -a / det_Jacobi(xi, eta);
}

double Quadrilateral_1_Element::eta_x(double xi, double eta)
{
    double a = 0;
    for (int i = 1; i <= 4; i++)
	    a = a + _dofslist[i-1][1]*phi_xi(xi, eta, i);
    return -a / det_Jacobi(xi, eta);
}

double Quadrilateral_1_Element::eta_y(double xi, double eta) 
{
    double a = 0;
    for (int i = 1; i <= 4; i++)
	    a = a + _dofslist[i-1][0]*phi_xi(xi, eta, i);
    return a / det_Jacobi(xi, eta);
}

double Quadrilateral_1_Element::phi_x(double xi, double eta, int i) 
{
    return phi_xi(xi, eta, i)*xi_x(xi, eta) + phi_eta(xi, eta, i)*eta_x(xi, eta);
}

double Quadrilateral_1_Element::phi_y(double xi, double eta, int i) 
{
    return phi_xi(xi, eta, i)*xi_y(xi, eta) + phi_eta(xi, eta, i)*eta_y(xi, eta);
}

std::vector<double> Quadrilateral_1_Element::gradient(double xi,double eta,int i)
{
    std::vector<double> gradient({phi_x(xi,eta,i),phi_y(xi,eta,i)});
    return gradient;
}
double Quadrilateral_1_Element::Global_x(double xi, double eta) 
{
    double a = 0;
    for (int i = 1; i <= 4; i++)
    {
	    a += _dofslist[i-1][0] * phi(xi, eta, i);
    }
    return a;
}

double Quadrilateral_1_Element::Global_y(double xi, double eta) 
{
    double a = 0;
    for (int i = 1; i <= 4; i++)
    {
	    a += _dofslist[i-1][1] * phi(xi, eta, i);
    }
    return a;
}

int Quadrilateral_1_Element::GetGlobalIndex(int i)
{
    return  _dofslist[i - 1].GetGlobalIndex();
}

void reinit(Grid<2>& _grid)
{

};
#else
#endif
