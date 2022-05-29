//
// Created by jgier on 25.05.2022.
//

#ifndef SIMPLEX_LINEAR_ALGEBRA_H
#define SIMPLEX_LINEAR_ALGEBRA_H

#include <vector>
#include <string>

using Value = double;
using Row = std::vector<Value>;
using Column = std::vector<Value>;
using Matrix = std::vector<Row>;

constexpr Value EPSILON = 1e-8;

Value multiply(Row row, Column column);
Row multiply(Row row, Value value);
Column multiply(const Matrix &matrix, const Column &column);

Row negate(Row const& row);

void add(Row & a, Row const& b);

void print(const Matrix &matrix);
void print(const Row& row, std::string const& left ="(", std::string const& right = ")");

#endif //SIMPLEX_LINEAR_ALGEBRA_H
