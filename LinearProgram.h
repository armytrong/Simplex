//
// Created by jgier on 25.05.2022.
//

#ifndef SIMPLEX_LINEARPROGRAM_H
#define SIMPLEX_LINEARPROGRAM_H

#include "linear_algebra.h"
#include "Solver.h"

class LinearProgram {
public:
    enum State {UNSOLVED, SOLVED [[maybe_unused]], OPTIMAL [[maybe_unused]]
    };

    LinearProgram(Column target_vector, Matrix constraints_matrix, Column constraints_vector);

    [[maybe_unused]] void optimize();

    [[maybe_unused]] void make_constraints_vector_non_negative();

    [[maybe_unused]] [[nodiscard]] Row const& target_vector() const;
    [[nodiscard]] Column const& constraints_vector() const;
    [[nodiscard]] Matrix const& constraints_matrix() const;

    [[nodiscard]] size_t num_variables() const;
    [[nodiscard]] size_t num_equations() const;



private:
    Row _target_vector;              // c
    Column _constraints_vector;       // b
    Matrix _constraints_matrix;       // A

    Column _solution;

    [[maybe_unused]] State _state;



};


#endif //SIMPLEX_LINEARPROGRAM_H
