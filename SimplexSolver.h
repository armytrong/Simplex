//
// Created by jgier on 25.05.2022.
//

#ifndef SIMPLEX_SIMPLEXSOLVER_H
#define SIMPLEX_SIMPLEXSOLVER_H

#include <optional>
#include "linear_algebra.h"
#include "SimplexTableau.h"


class SimplexSolver {
public:
    explicit SimplexSolver(LinearProgram &linear_program);

    State solve();

private:

    /*
     * The extended simplex tableau referres to the addition of variables with the purpose of omputing an initial
     * solution.
     */
    [[nodiscard]] SimplexTableau create_extended_simplex_tableau() const;

    LinearProgram &_linear_program;

};


#endif //SIMPLEX_SIMPLEXSOLVER_H
