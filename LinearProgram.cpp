//
// Created by jgier on 25.05.2022.
//

#include <cassert>
#include <iostream>
#include <sstream>
#include "LinearProgram.h"
#include "SimplexSolver.h"
#include "linear_algebra.h"


[[maybe_unused]] LinearProgram::LinearProgram(Column target_vector, Matrix constraints_matrix, Column constraints_vector) :
        _target_vector(std::move(target_vector)),
        _constraints_vector(std::move(constraints_vector)),
        _constraints_matrix(std::move(constraints_matrix)) {
    _state = UNSOLVED;
    _solution = Column(size(_target_vector));
    print();
}

void LinearProgram::maximize() {
    SimplexSolver simplex_solver(*this);
    _state = simplex_solver.solve();
}

void LinearProgram::make_constraints_vector_non_negative() {
    for (size_t i = 0; i < _constraints_vector.size(); i++) {
        if (_constraints_vector[i] < 0) {
            _constraints_vector[i] *= -1;
            for (size_t j = 0; j < _constraints_matrix[i].size(); j++) {
                _constraints_matrix[i][j] *= -1;
            }
        }
    }
}

[[maybe_unused]] Row const &LinearProgram::target_vector() const {
    return _target_vector;
}

Column const &LinearProgram::constraints_vector() const {
    return _constraints_vector;
}

Matrix const &LinearProgram::constraints_matrix() const {
    return _constraints_matrix;
}

size_t LinearProgram::num_variables() const {
    return _target_vector.size();
}

size_t LinearProgram::num_equations() const {
    return _constraints_vector.size();
}

void LinearProgram::set_solution(Column soluiton) {
    assert(is_solution(soluiton));
    _solution = std::move(soluiton);
}

bool LinearProgram::is_solution(const Column &solution) const {
    Column temp = multiply(_constraints_matrix,solution);
    if(temp.size() != _constraints_vector.size()) return false;
    for(VarID i = 0; i < temp.size(); i++){
        if(temp[i] - _constraints_vector[i] > EPSILON) return false;
    }
    return true;
}

Column LinearProgram::get_solution() const {
    return _solution;
}

Value LinearProgram::get_solution_value() const {
    return multiply(_target_vector,_solution);
}

State LinearProgram::state() const {
    return _state;
}

void LinearProgram::print() {
    std::cout << "Target Vector: ";
    ::print(_target_vector);
    std::cout << std::endl << "Constraints Matrix:" << std::endl;
    ::print(_constraints_matrix);
    std::cout << "Constraints Vector: ";
    ::print(_constraints_vector);
    std::cout << std::endl <<std::endl;
}

LinearProgram::LinearProgram(std::basic_istream<char> &file) {
    VarID num_equations, num_variables;
    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);
    ss >> num_equations >> num_variables;

    std::getline(file, line);
    ss = std::stringstream(line);
    for (VarID i = 0; i < num_variables; i++) {
        Value val;
        ss >> val;
        _target_vector.push_back(val);
    }

    std::getline(file, line);
    ss = std::stringstream(line);
    for (VarID i = 0; i < num_equations; i++) {
        Value val;
        ss >> val;
        _constraints_vector.push_back(val);
    }

    _constraints_matrix.resize(num_equations);
    for (VarID i = 0; i < num_equations; i++) {
        std::getline(file, line);
        ss = std::stringstream(line);
        for (VarID j = 0; j < num_variables; j++) {
            Value val;
            ss >> val;
            _constraints_matrix[i].push_back(val);
        }
    }

    _state = UNSOLVED;
    _solution = Column(size(_target_vector));
    print();
}
