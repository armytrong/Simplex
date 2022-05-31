cmake_minimum_required(VERSION 3.16)
project(Simplex)

set(CMAKE_CXX_STANDARD 20)

add_executable(Simplex main.cpp LinearProgram.cpp LinearProgram.h typedef.h linear_algebra.cpp linear_algebra.h SimplexSolver.cpp SimplexSolver.h SimplexTableau.cpp SimplexTableau.h)
