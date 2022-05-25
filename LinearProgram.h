//
// Created by jgier on 25.05.2022.
//

#ifndef SIMPLEX_LINEARPROGRAM_H
#define SIMPLEX_LINEARPROGRAM_H

#include "linear_algebra.h"
#include "Solver.h"

class LinearProgram {
public:
    enum State {UNSOLVED, SOLVED, OPTIMAL};

    LinearProgram(Column target_vector, Column constraints_vector, Matrix constraints_matrix);

    void optimize();

    void make_constraints_vector_non_negative();


private:
    Row _target_vector;              // c
    Column _constraints_vector;       // b
    Matrix _constraints_matrix;       // A

    Column _solution;

    State _state;



};


#endif //SIMPLEX_LINEARPROGRAM_H
