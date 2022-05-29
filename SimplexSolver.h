//
// Created by jgier on 25.05.2022.
//

#ifndef SIMPLEX_SIMPLEXSOLVER_H
#define SIMPLEX_SIMPLEXSOLVER_H

#include <optional>
#include "Solver.h"
#include "linear_algebra.h"
#include "SimplexTableau.h"


class SimplexSolver : public Solver {
public:
    explicit SimplexSolver(LinearProgram &linear_program);

    State solve() override;

private:

    [[nodiscard]] SimplexTableau create_extended_simplex_tableau();

};


#endif //SIMPLEX_SIMPLEXSOLVER_H
