//
// Created by jgier on 25.05.2022.
//

#ifndef SIMPLEX_TYPEDEF_H
#define SIMPLEX_TYPEDEF_H

class LinearProgram;

enum State {UNSOLVED, SOLVED, OPTIMAL, INFEASIBLE, UNBOUNDED};

using VarID = size_t;

#endif //SIMPLEX_TYPEDEF_H
