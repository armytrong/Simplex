//
// Created by jgier on 25.05.2022.
//

#include "SimplexSolver.h"

void SimplexSolver::solve() {
    Row start_solution_basis = compute_basis_with_fesible_solution();
    solve(start_solution_basis);
}

void SimplexSolver::solve(Row basis) {

}

Row SimplexSolver::compute_basis_with_fesible_solution() {
    return Row();
}

