//
// Created by jgier on 25.05.2022.
//

#ifndef SIMPLEX_LINEAR_ALGEBRA_H
#define SIMPLEX_LINEAR_ALGEBRA_H

#include <vector>
#include <string>

/*
 * This is a collection of functions and usings to make linear algebra calculations more concise.
 */



using Value = double;
using Row = std::vector<Value>;
using Column = std::vector<Value>;
using Matrix = std::vector<Row>;
/*
 * This serves as a threshhold. Values that are absolutely smaller than epsilon may be disregarded, as the algorithm
 * will otherwise not run correctly (because of floating point arithmetic erros).
 */

constexpr Value EPSILON = 1e-8;

Value multiply(Row row, Column column);
Row multiply(Row row, Value value);
Column multiply(const Matrix &matrix, const Column &column);

Row negate(Row const &row);

void add(Row &a, Row const &b);

void print(const Matrix &matrix);
void print(const Row &row, std::string const &left = "(", std::string const &right = ")");

#endif //SIMPLEX_LINEAR_ALGEBRA_H
