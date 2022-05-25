//
// Created by jgier on 25.05.2022.
//

#ifndef SIMPLEX_SOLVER_H
#define SIMPLEX_SOLVER_H
class LinearProgram;

class Solver {
public:
    explicit Solver(LinearProgram & linear_program) : _linear_program(linear_program){}

    virtual void solve() = 0;
private:
    LinearProgram & _linear_program;
};


#endif //SIMPLEX_SOLVER_H
