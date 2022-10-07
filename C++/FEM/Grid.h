#ifndef _GRID_
#define _GRID_

#include "TemplateElement.h"
#include "Point.h"
#include <vector>
using namespace std;
// DIM=2
template<unsigned int DIM>
class Grid
{
 protected:
     int num_of_vertices;
     //逆时针顺序
     vector<Point<DIM>> vertices;
     int num_of_dofs;
     vector<Dofs<DIM>> dofs;
 public:
     Grid(const vector<Point<DIM>>& _pnts);
     virtual ~Grid();

     void SetVertices(const vector<Point<DIM>>& _pnts)
     {
        vertices.resize(_pnts.size());
        copy(_pnts.begin(),_pnts.end(),vertices);
     };

     const vector<Point<DIM>>& GetVertices() const
     {
        return vertices;
     }
     const Point<DIM>& GetVertices(int _index) const
     {
        return vertices[_index-1];
     };

     const int GetNumVertices() const
     {
        return num_of_vertices;
     };

     void SetDofs(const vector<Dofs<DIM>>& _dofs)
     {
        dofs.resize(_dofs.size());
        copy(_dofs.begin(),_dofs.end(),dofs);
     };

     const Dofs<DIM>& GetDofs(int _index) const
     {
        return dofs[_index-1];
     };
     const int GetNumDofs() const
     {
        return num_of_dofs;
     };
};

template<unsigned int DIM>
Grid<DIM>::Grid(const vector<Point<DIM>>& _pnt) : vertices{_pnt}
{
    num_of_vertices = _pnt.size();
}


#else
// Do Nothing
#endif
