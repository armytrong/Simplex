#include <iostream>
#include <fstream>
#include <sstream>

#include "linear_algebra.h"
#include "typedef.h"
#include "LinearProgram.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Error: specify source." << std::endl;
        return 1;
    }

    auto file = std::ifstream(argv[1]);
    if (not file) {
        std::cerr << "Error: cannot open file." << std::endl;
        return 1;
    }

    VarID num_equations, num_variables;
    Row target_vector;
    Column constraits_vector;
    Matrix constraints_matrix;

    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);
    ss >> num_equations >> num_variables;

    std::getline(file, line);
    ss = std::stringstream(line);
    for (VarID i = 0; i < num_variables; i++) {
        Value val;
        ss >> val;
        target_vector.push_back(val);
    }

    std::getline(file, line);
    ss = std::stringstream(line);
    for (VarID i = 0; i < num_equations; i++) {
        Value val;
        ss >> val;
        constraits_vector.push_back(val);
    }

    constraints_matrix.resize(num_equations);
    for (VarID i = 0; i < num_equations; i++) {
        std::getline(file, line);
        ss = std::stringstream(line);
        for (VarID j = 0; j < num_variables; j++) {
            std::cout << i << ", " << j << std::endl;
            Value val;
            ss >> val;
            constraints_matrix[i].push_back(val);
        }
    }

    LinearProgram linear_program(target_vector, constraints_matrix, constraits_vector);
    linear_program.maximize();

    switch (linear_program.state()) {
        case UNBOUNDED:
            std::cout << "The LP is unbounded. A solution is ";
            print(linear_program.get_solution());
            std::cout << std::endl;
            break;
        case OPTIMAL:
            std::cout << "An optimal solution is ";
            print(linear_program.get_solution());
            std::cout << " with value " << linear_program.get_solution_value() << std::endl;
            break;
        case INFEASIBLE:
            std::cout << "The LP is infeasible." << std::endl;
            break;
        default:
            std::cerr << "Something went wrong." << std::endl;
    }


    return 0;
}
