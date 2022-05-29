#include <iostream>
#include <fstream>
#include <iomanip>

#include "linear_algebra.h"
#include "typedef.h"
#include "LinearProgram.h"


int main(int argc, char **argv) {

    std::cout << std::setprecision(2);

    if (argc < 2) {
        std::cerr << "Error: specify source." << std::endl;
        return 1;
    }

    auto file = std::ifstream(argv[1]);
    if (not file) {
        std::cerr << "Error: cannot open file." << std::endl;
        return 1;
    }

    LinearProgram linear_program(file);

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
