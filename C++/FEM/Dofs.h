#ifndef _DOFS_
#define _DOFS_

#include "Point.h"
/**
 * 
 * @brief  继承点类，增加全局编号
 */

template <unsigned int Dim>
class Dofs : public Point<Dim>
{
public:
    Dofs();
    Dofs(const std::vector<double> _pnt, int _global_index):Point{_pnt},globalIndex{_global_index};
    ~Dofs();
    
    void SetGlobalIndex(const int i){globalIndex=i;};
    int& GetGlobalIndex(){return  globalIndex;};
    double& operator[](const unsigned int d){
	    return Point<Dim>::value[d];
    };

    template<unsigned int D>
    friend std::ostream& operator<<(std::ostream& os, const Dofs<D>& dof);

private:
    int globalIndex;
};

template<unsigned int D>
std::ostream& operator<<(std::ostream& os, const Dofs<D>& dof){
    os << dof._GlbIdx << " : ";
    os << "( ";
    for (unsigned int d = 0; d < D - 1; d++)
    {
        os << dof.Point<D>::_value[d] << " , ";
    }
    os << dof.Point<D>::_value[D - 1] << " )";
    return os;
}

#else
// Do Nothing
#endif
