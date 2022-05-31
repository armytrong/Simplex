//
// Created by jgier on 26.05.2022.
//

#include "SimplexTableau.h"
#include <cassert>
#include <iostream>
#include <iomanip>



SimplexTableau::SimplexTableau(
        std::vector<bool> index_in_basis,
        Column constant_summands_of_equations,
        Matrix linear_coeffitients_of_equations,
        Value constant_term_of_target_equation,
        Row linear_coeffitients_of_target_equation
):
       _index_in_basis(std::move(index_in_basis)),
       _constant_summands_of_equations(std::move(constant_summands_of_equations)),
       _linear_coeffitients_of_equations(std::move(linear_coeffitients_of_equations)),
       _constant_term_of_target_equation(constant_term_of_target_equation),
       _linear_coeffitients_of_target_equation(std::move(linear_coeffitients_of_target_equation))
{}

State SimplexTableau::iterate() {
    auto new_basis_index = blands_rule_new_basis_index();
    if (not new_basis_index.has_value()) {
        return OPTIMAL;
    }
    auto old_basis_index = blands_rule_old_basis_index(new_basis_index.value());
    if (not old_basis_index.has_value()) {
        return UNBOUNDED;
    }
    switch_basis_elements(new_basis_index.value(), old_basis_index.value());
    return SOLVED;
}

std::optional<VarID> SimplexTableau::blands_rule_new_basis_index() const {
    for (VarID i = 0; i < _linear_coeffitients_of_target_equation.size(); i++) {
        if (_linear_coeffitients_of_target_equation[i] - EPSILON > 0) return i;
    }
    return std::nullopt;
}

std::optional<VarID> SimplexTableau::blands_rule_old_basis_index(VarID new_basis_index) const {
    std::optional<VarID> result = std::nullopt;
    double current_max = -std::numeric_limits<Value>::infinity();
    for (VarID i = 0; i < _linear_coeffitients_of_equations.size(); i++) {
        if (_linear_coeffitients_of_equations[i][new_basis_index] + EPSILON < 0 &&
            _constant_summands_of_equations[i] / _linear_coeffitients_of_equations[i][new_basis_index] > current_max) {
            result = i;
            current_max = _constant_summands_of_equations[i] / _linear_coeffitients_of_equations[i][new_basis_index];
        }
    }
    return result;
}

void SimplexTableau::switch_basis_elements(VarID new_index, VarID old_index) {
    assert(_index_in_basis[new_index] == false && "new index must not already be in basis");
    assert(_index_in_basis[old_index] == true && "old index must stem from basis");

    /*
     * These are all computations to transfer the tableau from the previous Basis to the new Basis. They result
     * directly from plugging the equations into one another.
     */
    _constant_summands_of_equations[new_index] =
            -_constant_summands_of_equations[old_index] / _linear_coeffitients_of_equations[old_index][new_index];
    assert(_constant_summands_of_equations[new_index] + EPSILON >= 0 && "Solution must be >= 0 at all times");
    _constant_summands_of_equations[old_index] = 0;

    for (VarID i = 0; i < _constant_summands_of_equations.size(); i++) {
        if(i == new_index or i == old_index) continue;
        _constant_summands_of_equations[i] += _linear_coeffitients_of_equations[i][new_index]
                * _constant_summands_of_equations[new_index];
    }

    for (VarID i = 0; i < _linear_coeffitients_of_equations[new_index].size(); i++) {
        if (i == new_index) {
            _linear_coeffitients_of_equations[new_index][i] = 0;
        } else if (i == old_index) {
            _linear_coeffitients_of_equations[new_index][i] =
                    1 / _linear_coeffitients_of_equations[old_index][new_index]; // -1?
        } else {
            _linear_coeffitients_of_equations[new_index][i] = -_linear_coeffitients_of_equations[old_index][i] /
                                                              _linear_coeffitients_of_equations[old_index][new_index];
        }
    }
    for (VarID i = 0; i < _linear_coeffitients_of_equations[new_index].size(); i++) {
        _linear_coeffitients_of_equations[old_index][i] = 0;
    }


    for (VarID i = 0; i < _linear_coeffitients_of_equations.size(); i++) {
        if (i == new_index or i == old_index or not _index_in_basis[i]) continue;
        auto old_coeffitient = _linear_coeffitients_of_equations[i][new_index];
        for (VarID j = 0; j < _linear_coeffitients_of_equations[i].size(); j++) {
            if (j == new_index) {
                _linear_coeffitients_of_equations[i][j] = 0;
            } else {
                _linear_coeffitients_of_equations[i][j] +=
                        old_coeffitient * _linear_coeffitients_of_equations[new_index][j];
            }
        }
    }

    _constant_term_of_target_equation +=
            _linear_coeffitients_of_target_equation[new_index] * _constant_summands_of_equations[new_index];
    auto old_coeffitient = _linear_coeffitients_of_target_equation[new_index];
    for (VarID i = 0; i < _linear_coeffitients_of_target_equation.size(); i++) {
        _linear_coeffitients_of_target_equation[i] += old_coeffitient * _linear_coeffitients_of_equations[new_index][i];
    }
    _linear_coeffitients_of_target_equation[new_index] = 0;

    _index_in_basis[new_index] = true;
    _index_in_basis[old_index] = false;
}

Column SimplexTableau::extract_solution() const {
    return _constant_summands_of_equations;
}

bool SimplexTableau::crop_tableau(VarID num_slack_variables_to_crop) {
    const VarID num_remaining_variables = _constant_summands_of_equations.size() - num_slack_variables_to_crop;
    std::vector<VarID> remaining_variables_not_in_basis;
    for(VarID i = 0; i < num_remaining_variables; i++){
        if(not _index_in_basis[i]){
            remaining_variables_not_in_basis.push_back(i);
        }
    }
    for(VarID i = num_remaining_variables; i < num_remaining_variables + num_slack_variables_to_crop; i++){
        if(_index_in_basis[i]){
            if(_constant_summands_of_equations[i] != 0){
                return false; // cannot crop, bc a none zero element is to be cropped.
            }
            VarID new_index = remaining_variables_not_in_basis.back();
            switch_basis_elements(new_index, i);
            remaining_variables_not_in_basis.pop_back();
            assert(_constant_summands_of_equations[new_index] == 0 && "Variables, that are swapped into the basis "
                                                                      "while cropping have to remain 0");
        }
    }
    _constant_summands_of_equations.resize(num_remaining_variables);
    _linear_coeffitients_of_equations.resize(num_remaining_variables);
    _linear_coeffitients_of_target_equation.resize(num_remaining_variables);
    for(auto & row : _linear_coeffitients_of_equations){
        row.resize(num_remaining_variables);
    }
    _index_in_basis.resize(num_remaining_variables);
    return true;
}

void SimplexTableau::set_target_equation(Value constant_term, Row linear_coeffitients) {
    assert(linear_coeffitients.size() == _linear_coeffitients_of_target_equation.size());
    _constant_term_of_target_equation = constant_term;
    _linear_coeffitients_of_target_equation = std::move(linear_coeffitients);

    for(VarID i = 0; i < _linear_coeffitients_of_target_equation.size(); i++){
        if(_index_in_basis[i] && _linear_coeffitients_of_target_equation[i] != 0){
            add(_linear_coeffitients_of_target_equation, multiply(_linear_coeffitients_of_equations[i],
                                                                  _linear_coeffitients_of_target_equation[i]));
            _constant_term_of_target_equation += _constant_summands_of_equations[i] *
                    _linear_coeffitients_of_target_equation[i];
            _linear_coeffitients_of_target_equation[i] = 0;
        }
    }
}

void SimplexTableau::print(){
    for(VarID i = 0; i < _constant_summands_of_equations.size(); i++){
        if(_index_in_basis[i]){
            std::cout << "x_" << i << " = " << std::fixed << std::setw(6) << _constant_summands_of_equations[i];
            for(VarID j = 0; j < _linear_coeffitients_of_equations[i].size(); j++){
                if(not _index_in_basis[j]){
                    Value print_value = std::abs(_linear_coeffitients_of_equations[i][j]);
                    std::string sign = _linear_coeffitients_of_equations[i][j] >= 0 ? " + " : " - ";
                    std::cout << sign << std::fixed << std::setw(6) << print_value << "x_"<< j;
                }
            }
            std::cout << std::endl;
        }
    }
    std::cout << "---------------------------------------------------------------------------------------------------"
    << std::endl;

    std::cout << "  z = " << std::fixed << std::setw(6) << _constant_term_of_target_equation;
    for(VarID j = 0; j < _linear_coeffitients_of_target_equation.size(); j++){
        if(not _index_in_basis[j]){
            Value print_value = std::abs(_linear_coeffitients_of_target_equation[j]);
            std::string sign = _linear_coeffitients_of_target_equation[j] >= 0 ? " + " : " - ";
            std::cout << sign << std::fixed << std::setw(6) << print_value << "x_"<< j;
        }
    }
    std::cout << std::endl <<std::endl;

}
