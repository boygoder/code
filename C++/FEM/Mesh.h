#ifndef _MESH_
#define _MESH_

#include "Domain.h"
#include "Dofs.h"
#include "Grid.h"

template <unsigned int DIM>
class Mesh
{
public:
    Mesh();
    Mesh(Domain<DIM> domain, vector<int> seg);
    ~Mesh();

    int GetNumGrid();
    Grid<DIM> &GetGrid(int _index);
    //返回边界上自由度的globalIndex
    vector<int>& GetBoundaryIndex();
    //假定所有单元类型、阶数都相同
    void DistributeDofs(int _order_of_element = 1);
    //_GridList.size()*get_num_dofs();
    int TotalNumDofs();

private:
    vector<Grid<DIM>> _GridList;
};

template <unsigned int DIM>
Mesh<DIM>::Mesh(Domain<DIM> domain, vector<int> seg)
{
    assert(DIM==2 && seg.size() == DIM);

};

template <unsigned int DIM>
int Mesh<DIM>::GetNumGrid()
{
    return _GridList.size();
};

template <unsigned int DIM>
Grid<DIM> &Mesh<DIM>::GetGrid(int _index)
{
    return _GridList[_index];
};

template <unsigned int DIM>
vector<int>&  Mesh<DIM>::GetBoundaryIndex()
{
    //对所有grid,依据seg找出边界的grid,再确定对应边界的自由度下标是哪几个
};

//假定所有单元类型、阶数都相同
template <unsigned int DIM>
void Mesh<DIM>::DistributeDofs(int _order_of_element = 1)
{
    //以下示范DIM=2，_order_of_element = 2;
    assert(DIM ==2 && _order_of_element == 2);
    int global_idx = 0;
    for (Grid<DIM> &grid : _GridList)
    {
        const vector<Point<DIM>> p = grid.GetVertices();
        vector<Dofs<DIM>> _dofs;
        _dofs.push_back({p[0][0], p[0][1]}, global_idx++);
        _dofs.push_back({(p[0][0] + p[1][0])/2.0, (p[0][1] + p[1][1])/2.0}, global_idx++);
        _dofs.push_back({p[1][0], p[1][1]}, global_idx++);
        _dofs.push_back({(p[1][0]+p[2][0])/2.0,(p[1][1] + p[2][1])/2.0}, global_idx++);
        _dofs.push_back({p[2][0],p[2][1]}, global_idx++);
        _dofs.push_back({(p[2][0]+p[3][0])/2.0,(p[2][1]+p[3][1]/2.0)}, global_idx++);
        _dofs.push_back({p[3][0],p[3][1]}, global_idx++);
        _dofs.push_back({(p[3][0]+p[0][0])/2.0,(p[3][1]+p[0][1])/2.0}, global_idx++);
        _dofs.push_back({(p[0][0]+p[2][0])/2.0,(p[0][1]+p[2][1])/2.0}, global_idx++);
        grid.SetDofs(_dofs);
    }
};

template <unsigned int DIM>
long int TotalNumDofs()
{
    long int res = 0;
    for (Grid<DIM> grid : _GridList)
    {
        res += grid.get_num_dofs();
    }
    return res;
};

#else
#endif
