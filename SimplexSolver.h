//
// Created by jgier on 25.05.2022.
//

#ifndef SIMPLEX_SIMPLEXSOLVER_H
#define SIMPLEX_SIMPLEXSOLVER_H

#include <optional>
#include "Solver.h"
#include "linear_algebra.h"


class SimplexSolver : public Solver {
public:
    explicit SimplexSolver(LinearProgram &linear_program, std::optional<Row> feasible_basis = std::nullopt) :
            Solver(linear_program), _feasible_basis(std::move(feasible_basis)) {}

    void solve() override;

    Row solve(Row basis);

private:
    [[nodiscard]] Matrix construct_auxiliary_constraits_matrix() const;

    [[nodiscard]] Row construct_auxiliary_target_vector() const;

    [[nodiscard]] Row construct_auxiliary_basis() const;

    [[nodiscard]] Row compute_basis_with_feasible_solution();

    std::optional<Row> _feasible_basis;
};


#endif //SIMPLEX_SIMPLEXSOLVER_H
