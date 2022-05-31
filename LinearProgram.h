//
// Created by jgier on 25.05.2022.
//

#ifndef SIMPLEX_LINEARPROGRAM_H
#define SIMPLEX_LINEARPROGRAM_H

#include "linear_algebra.h"
#include "typedef.h"
#include <istream>

/// Class to store a linear program
class LinearProgram {
public:

    /*
     * Import a linear program from a file with the format given in the task.
     */
    explicit LinearProgram(std::basic_istream<char> & file);

    [[maybe_unused]] LinearProgram(Column target_vector, Matrix constraints_matrix, Column constraints_vector);

    void maximize();

    void make_constraints_vector_non_negative();

    /// Getters
    [[nodiscard]] Row const& target_vector() const;
    [[nodiscard]] Column const& constraints_vector() const;
    [[nodiscard]] Matrix const& constraints_matrix() const;

    [[nodiscard]] Column solution() const;
    [[nodiscard]] Value solution_value() const;

    [[nodiscard]] State state() const;

    [[nodiscard]] size_t num_variables() const;
    [[nodiscard]] size_t num_equations() const;

    /// Setter
    void set_solution(Column soluiton);

    [[nodiscard]] bool verify_solution(Column const& solution) const;

    void print();



private:
    Row _target_vector;              // c
    Column _constraints_vector;       // b
    Matrix _constraints_matrix;       // A

    Column _solution;

    State _state;



};


#endif //SIMPLEX_LINEARPROGRAM_H
