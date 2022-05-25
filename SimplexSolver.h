//
// Created by jgier on 25.05.2022.
//

#ifndef SIMPLEX_SIMPLEXSOLVER_H
#define SIMPLEX_SIMPLEXSOLVER_H

#include "Solver.h"
#include "linear_algebra.h"


class SimplexSolver : public Solver {
public:
    explicit SimplexSolver(LinearProgram & linear_program) : Solver(linear_program){}

    void solve() override;
    void solve(Row basis);
private:
    Row compute_basis_with_fesible_solution();
};


#endif //SIMPLEX_SIMPLEXSOLVER_H
