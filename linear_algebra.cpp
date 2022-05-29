//
// Created by jgier on 25.05.2022.
//

#include "linear_algebra.h"
#include <cassert>
#include <iostream>
#include <iomanip>

Value multiply(Row row, Column column){
    assert(row.size() == column.size() && "Cannot multiply vectors of different dimension.");
    Value ret = 0;
    for(size_t i = 0; i < row.size(); i++) {
        ret += row[i] * column[i];
    }
    return ret;
}

[[maybe_unused]] Column multiply(const Matrix &matrix, const Column &column){
    Column ret(matrix.size(), 0);
    for (size_t i = 0; i < ret.size(); i++) {
        ret[i] = multiply(matrix[i], column);
    }
    return ret;
}

Row negate(Row const& row){
    Row ret(row);
    for(Value & val : ret){
         val *= -1;
    }
    return ret;
}

void add(Row & a, Row const& b){
    for(size_t i = 0; i < std::min(a.size(), b.size()); i++){
        a[i] += b[i];
    }
}

Row multiply(Row row, Value value){
    for(double & i : row){
        i *= value;
    }
    return row;
}

void print(const Matrix &matrix){
    for(auto const& row : matrix){
        print(row, "|", "|\n");
    }
}
void print(const Row& row, std::string const& left, std::string const& right){
    std::cout << left;
    for(size_t i = 0; i < row.size()-1; i++){
        std::cout << std::fixed << std::setw(6) << row[i] << ", ";
    }
    std::cout << std::fixed << std::setw(6) << row.back() << right;
}
