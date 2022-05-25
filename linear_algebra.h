//
// Created by jgier on 25.05.2022.
//

#ifndef SIMPLEX_LINEAR_ALGEBRA_H
#define SIMPLEX_LINEAR_ALGEBRA_H

#include <vector>

using Value = double;
using Row = std::vector<Value>;
using Column = std::vector<Value>;
using Matrix = std::vector<Row>;

Value multiply(Row row, Column column);
Column muliply(Matrix matrix, Column column);


#endif //SIMPLEX_LINEAR_ALGEBRA_H
