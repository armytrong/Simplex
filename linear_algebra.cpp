//
// Created by jgier on 25.05.2022.
//

#include "linear_algebra.h"
#include <cassert>

Value multiply(Row row, Column column){
    assert(row.size() == column.size() && "Cannot multiply vectors of different dimension.");
    Value ret = 0;
    for(size_t i = 0; i < row.size(); i++) {
        ret += row[i] * column[i];
    }
}

Column muliply(Matrix matrix, Column column){
    Column ret(matrix.size(), 0);
    for (size_t i = 0; i < ret.size(); i++) {
        ret[i] = multiply(matrix[i], column);
    }
}