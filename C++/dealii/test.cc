/* ---------------------------------------------------------------------
 *
 * Copyright (C) 1999 - 2022 by the deal.II authors
 *
 * This file is part of the deal.II library.
 *
 * The deal.II library is free software; you can use it, redistribute
 * it, and/or modify it under the terms of the GNU Lesser General
 * Public License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * The full text of the license can be found in the file LICENSE.md at
 * the top level directory of deal.II.
 *
 * ---------------------------------------------------------------------

 *
 * Authors: Wolfgang Bangerth, 1999,
 *          Guido Kanschat, 2011
 */


/* handle triangulations*/
#include <deal.II/grid/tria.h>
/* enumeration of degrees of freedom*/
#include <deal.II/dofs/dof_handler.h>
/*create grids*/
#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/grid_out.h>
/*this file contains the description of the Lagrange interpolation finite element */
#include <deal.II/fe/fe_q.h>
/*this file is needed for the creation of sparsity patterns of sparse matrices*/
#include <deal.II/dofs/dof_tools.h>

/**
 * the next two files are needed for assembling the matrix using quadrature on each cell
 * fe_values.h:values of the shape functions computed is update_values; 
 *             for the gradients it is update_gradients. 
 *             The determinants of the Jacobians and the quadrature weights are update_JxW_values.
 */
#include <deal.II/fe/fe_values.h>
#include <deal.II/base/quadrature_lib.h>
/*for the treatment of boundary values.*/
#include <deal.II/base/function.h>
#include <deal.II/numerics/vector_tools.h>
#include <deal.II/numerics/matrix_tools.h>
/*assembling the system of equations*/
#include <deal.II/lac/vector.h>
#include <deal.II/lac/full_matrix.h>
#include <deal.II/lac/sparse_matrix.h>
#include <deal.II/lac/dynamic_sparsity_pattern.h>

/*Conjugate Gradient solver*/
#include <deal.II/lac/solver_cg.h>
#include <deal.II/lac/precondition.h>

/*for output to a file and to the console*/
#include <deal.II/numerics/data_out.h>
#include <fstream>
#include <iostream>

using namespace dealii;



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

	Triangulation<2> triangulation;/**< 定义域的三角剖分 */
	FE_Q<2>          fe;/**< 单元的类型和阶数 */
	DoFHandler<2>    dof_handler;/**< 形函数 */

	SparsityPattern      sparsity_pattern;/**< 刚度矩阵的pattern */
	SparseMatrix<double> system_matrix;/**< 刚度矩阵 */

	Vector<double> solution;/**< 结果 */
	Vector<double> system_rhs;/**< 右端项*/
};


/**
 * FE_Q<2> fe(1);代表二维的1阶四边形单元。
 */
FEM::FEM()
	: fe(1), dof_handler(triangulation){}


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
 * This function does the first part, creating the mesh. We create the grid and refine all cells five times.
 * Since the initial grid (which is the square [−1,1]×[−1,1]) consists of only one cell,
 * the final grid has 32 * 32 cells, for a total of 1024.
 */
void FEM::make_grid()
{
    //GridGenerator::hyper_cube(triangulation, -1, 1);
	GridGenerator::hyper_rectangle(triangulation,{-1,-1},{1,1});
	//default boundary_id is 0.
	 // for(auto &face : triangulation.active_face_iterators())
	 // 	if (std::fabs(face->center()(1) - (-1.0)) < 1e-12 ||
	 // 		std::fabs(face->center()(1) - (1.0)) < 1e-12)
	 // 		face->set_boundary_id(1);


	triangulation.refine_global(5);

	std::cout << "Number of active cells: " << triangulation.n_active_cells()
			  << std::endl;
    std::ofstream out("grid.svg");
    GridOut grid_out;
    grid_out.write_svg(triangulation,out);
}



/**
 * Next we enumerate all the degrees of freedom and set up matrix and vector objects to hold the system data.
 *
 */
void FEM::setup_system()
{
	/*Enumerating is done by using DoFHandler::distribute_dofs().*/
	dof_handler.distribute_dofs(fe);
	std::cout << "Number of degrees of freedom: " << dof_handler.n_dofs()
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
