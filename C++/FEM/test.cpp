#include <fstream>
#include <iostream>

#include "Point.h"
#include "Dofs.h"
#include "GaussianPoint.h"
#include "Grid.h"
#include "TemplateElement.h"
#include "Domain.h"
#include "Mesh.h"


class FEM
{
public:
	FEM();
	void run();
private:

	void make_grid();
	void setup_system();
	void assemble_system();
	void solve();
	void output_results() const;

    Quadrilateral_1_Element _element;
    Rectangle2D _domain; 
    Mesh<2> _mesh;

	//SparseMatrix<double> system_matrix;/**< 刚度矩阵 */

	vector<double> solution;/**< 结果 */
	vector<double> system_rhs;/**< 右端项*/
};


/**
 * 初始化定义域 
 */
FEM::FEM()
{

};  


template <int dim>
class RightHandSide : public Function<dim>
{
public:
  virtual double value(const Point<dim> & p,
                       const unsigned int component = 0) const override;
};



template <int dim>
class BoundaryValues : public Function<dim>
{
public:
  virtual double value(const Point<dim> & p,
                       const unsigned int component = 0) const override;
};

template <int dim>
double RightHandSide<dim>::value(const Point<dim> &p,
                                 const unsigned int /*component*/) const
{
//   double return_value = 0.0;
//   for (unsigned int i = 0; i < dim; ++i)
//       return_value += 4.0 * std::pow(p(i), 4.0);
//   return return_value;
     return 1;
}


template <int dim>
double BoundaryValues<dim>::value(const Point<dim> &p,
                                  const unsigned int /*component*/) const
{
  //return p.square();
    return 0;
}


/**
 * This function does the first part, creating the mesh. We create the mesh
 * which is the square [−1,1]×[−1,1].
 */
void FEM::make_grid()
{
    vector<Point<2>> p = {{-1.0,-1.0},{1.0,-1.0},{1.0,1.0},{-1.0,1.0}};
    Rectangle2D domain(p);
    _domain = domain;

    Mesh<2> mesh(domain,{3,3});
    _mesh = mesh;
}



/**
 * Next we enumerate all the degrees of freedom and set up matrix and vector objects to hold the system data.
 *
 */
void FEM::setup_system()
{
	/*Enumerating is done by using DistributeDofs().*/
	_mesh.DistributeDofs(1);
	std::cout << "Number of degrees of freedom: " << _mesh.GetNumGrid()
			  << std::endl;

	/**
     * we set up a sparsity pattern by first creating a temporary structure,
	 * tagging those entries that might be nonzero,
	 * and then copying the data over to the SparsityPattern object 
     * that can then be used by the system matrix.
     */
	DynamicSparsityPattern dsp(dof_handler.n_dofs());
	DoFTools::make_sparsity_pattern(dof_handler, dsp);
	sparsity_pattern.copy_from(dsp);

	system_matrix.reinit(sparsity_pattern);

	/*set the sizes of the right hand side vector and the solution vector.*/
	solution.reinit(dof_handler.n_dofs());
	system_rhs.reinit(dof_handler.n_dofs());
}


/**
 * The next step is to compute the entries of the matrix
 * and right hand side that form the linear system from which we compute the solution.
 */
void FEM::assemble_system()
{
	/**
     * Generate a formula with n quadrature points (in each space direction), 
     * exact for polynomials of degree 2n-1.
     */
	QGauss<2> quadrature_formula(fe.degree + 1);
	RightHandSide<2> right_hand_side;
	/**
	 * update_values: the values of the shape functions;
	 * update_gradients: the gradient of shape functions;
	 * update_quadrature_points: the quadrature points on the cell we are presently on;
	 * update_JxW_values: The products of the Jacobians and the quadrature weights
     *                    (Jacobians times weights, or short JxW).
	 */
	FEValues<2> fe_values(fe,
						  quadrature_formula,
						  update_values | update_gradients | update_quadrature_points | update_JxW_values);

	const unsigned int dofs_per_cell = fe.n_dofs_per_cell();

	FullMatrix<double> cell_matrix(dofs_per_cell, dofs_per_cell);
	Vector<double>     cell_rhs(dofs_per_cell);


	std::vector<types::global_dof_index> local_dof_indices(dofs_per_cell);
	/*assemble the global matrix and vector cell-by-cell.*/
	for (const auto &cell : dof_handler.active_cell_iterators())
    {
		fe_values.reinit(cell);

		cell_matrix = 0;
		cell_rhs    = 0;

		for (const unsigned int q_index : fe_values.quadrature_point_indices())
        {
			for (const unsigned int i : fe_values.dof_indices())
				for (const unsigned int j : fe_values.dof_indices())
					cell_matrix(i, j) +=
						(fe_values.shape_grad(i, q_index) * // grad phi_i(x_q)
						 fe_values.shape_grad(j, q_index) * // grad phi_j(x_q)
						 fe_values.JxW(q_index));           // dx

			const auto &x_q = fe_values.quadrature_point(q_index);
			for (const unsigned int i : fe_values.dof_indices())
				cell_rhs(i) += (fe_values.shape_value(i, q_index) * // phi_i(x_q)
								right_hand_side.value(x_q) *        // f(x_q)
								fe_values.JxW(q_index));            // dx
        }

		cell->get_dof_indices(local_dof_indices);

		for (const unsigned int i : fe_values.dof_indices())
			for (const unsigned int j : fe_values.dof_indices())
				system_matrix.add(local_dof_indices[i],
								  local_dof_indices[j],
								  cell_matrix(i, j));

		for (const unsigned int i : fe_values.dof_indices())
			system_rhs(local_dof_indices[i]) += cell_rhs(i);
    }

	std::map<types::global_dof_index, double> boundary_values;
	/**
	 * dof_handler: To get the global numbers of the degrees of freedom on the boundary;
	 * 0: boundary_id, the component of the boundary where the boundary values shall be interpolated;
     * Functions::ZeroFunction<2>(): the boundary value function itself;
	 * boundary_values:  the output object, pairs of global degree of freedom numbers
	 *                   (i.e.the number of the degrees of freedom on the boundary)
	 *                   and their boundary values (which are zero here for all entries).
	 */
	VectorTools::interpolate_boundary_values(dof_handler,
											 0,
											 BoundaryValues<2>(),//Functions::ZeroFunction<2>(),
											 boundary_values);
	 // VectorTools::interpolate_boundary_values(dof_handler,
	 // 										  1,
	 // 										  Functions::ConstantFunction<2>(1.0),
	 // 										  boundary_values);
	MatrixTools::apply_boundary_values(boundary_values,
									   system_matrix,
									   solution,
									   system_rhs);
}



void FEM::solve()
{
	/**
	 *  stop after a maximum of 1000 iterations,
	 *  and stop if the norm of the residual is below τ=1e−6*||b|| where b is the right hand side vector
	 */
	SolverControl            solver_control(1000, 1e-6 * system_rhs.l2_norm());
	SolverCG<Vector<double>> solver(solver_control);
	solver.solve(system_matrix, solution, system_rhs, PreconditionIdentity());
}




void FEM::output_results() const
{
	DataOut<2> data_out; 
	data_out.attach_dof_handler(dof_handler);
	data_out.add_data_vector(solution, "solution");
    //data_out.add_data_vector(system_rhs,"system_rhs");
	data_out.build_patches();

	std::ofstream output("solution.vtk");
	data_out.write_vtk(output);

}



void FEM::run()
{
	make_grid();
	setup_system();
	assemble_system();
	solve();
	output_results();
}



int main()
{
	deallog.depth_console(2);

	FEM laplace_problem;
	laplace_problem.run();

	return 0;
}
