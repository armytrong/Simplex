//
// Created by jgier on 25.05.2022.
//

#include "SimplexSolver.h"
#include "LinearProgram.h"

void SimplexSolver::solve() {
    Row start_solution_basis = compute_basis_with_feasible_solution();
    solve(start_solution_basis);
}

Row SimplexSolver::solve(Row basis) {
    return {};
}

Row SimplexSolver::compute_basis_with_feasible_solution() {
    Matrix auxiliary_constraints_matrix = construct_auxiliary_constraits_matrix();
    Row auxiliary_target_vector = construct_auxiliary_target_vector();
    LinearProgram auxiliary_linear_program(
            auxiliary_target_vector,
            auxiliary_constraints_matrix,
            _linear_program.constraints_vector()
    );
    Row auxiliary_basis = construct_auxiliary_basis();
    SimplexSolver auxiliary_solver(auxiliary_linear_program, auxiliary_basis);
    return auxiliary_solver.solve(auxiliary_basis);
}

Matrix SimplexSolver::construct_auxiliary_constraits_matrix() const {
    Matrix const &constraints_matrix = _linear_program.constraints_matrix();
    Matrix ret{constraints_matrix};
    for (size_t i = 0; i < constraints_matrix.size(); i++) {
        for (size_t j = 0; j < constraints_matrix.size(); j++) {
            ret[i].push_back(static_cast<Value>(i == j));
        }
    }
    return ret;
}


Row SimplexSolver::construct_auxiliary_target_vector() const {
    Row ret;
    for (size_t i = 0; i < _linear_program.num_variables(); i++) {
        ret.push_back(0);
    }
    for (size_t i = 0; i < _linear_program.num_equations(); i++) {
        ret.push_back(-1);
    }
    return ret;
}

Row SimplexSolver::construct_auxiliary_basis() const{
    Row ret;
    for(size_t i = 0; i < _linear_program.num_equations(); i++){
        ret.push_back(static_cast<double>(i + _linear_program.num_variables()));
    }
    return ret;
}

