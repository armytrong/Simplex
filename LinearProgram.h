//
// Created by jgier on 25.05.2022.
//

#ifndef SIMPLEX_LINEARPROGRAM_H
#define SIMPLEX_LINEARPROGRAM_H

#include "linear_algebra.h"
#include "Solver.h"
#include "typedef.h"
#include <istream>

class LinearProgram {
public:

    explicit LinearProgram(std::basic_istream<char> & file);

    [[maybe_unused]] LinearProgram(Column target_vector, Matrix constraints_matrix, Column constraints_vector);

    void maximize();

    void make_constraints_vector_non_negative();

    [[nodiscard]] Row const& target_vector() const;
    [[nodiscard]] Column const& constraints_vector() const;
    [[nodiscard]] Matrix const& constraints_matrix() const;

    [[nodiscard]] size_t num_variables() const;
    [[nodiscard]] size_t num_equations() const;

    void set_solution(Column soluiton);
    [[nodiscard]] bool is_solution(Column const& solution) const;

    [[nodiscard]] Column get_solution() const;
    [[nodiscard]] Value get_solution_value() const;

    [[nodiscard]] State state() const;

    void print();



private:
    Row _target_vector;              // c
    Column _constraints_vector;       // b
    Matrix _constraints_matrix;       // A

    Column _solution;

    State _state;



};


#endif //SIMPLEX_LINEARPROGRAM_H
