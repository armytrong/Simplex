//
// Created by jgier on 26.05.2022.
//

#include "SimplexTableau.h"
#include <cassert>

SimplexTableau::SimplexTableau(const LinearProgram &linearProgram, std::vector<bool> basis) {

}

State SimplexTableau::iterate() {
    auto new_basis_index = blands_rule_new_basis_index();
    if (not new_basis_index.has_value()) {
        return OPTIMAL;
    }
    auto old_basis_index = blands_rule_old_basis_index(new_basis_index.value());
    if (not new_basis_index.has_value()) {
        return UNBOUNDED;
    }
    switch_basis_elements(new_basis_index.value(), old_basis_index.value());
    return UNSOLVED;
}

std::optional<VarID> SimplexTableau::blands_rule_new_basis_index() const {
    for (VarID i = 0; i < _linear_coeffitients_of_target_equation.size(); i++) {
        if (_linear_coeffitients_of_target_equation[i] > 0) return i;
    }
    return std::nullopt;
}

std::optional<VarID> SimplexTableau::blands_rule_old_basis_index(VarID new_basis_index) const {
    std::optional<VarID> result = std::nullopt;
    double current_max = 0;
    for (VarID i = 0; i < _linear_coeffitients_of_equations.size(); i++) {
        if (_linear_coeffitients_of_equations[i][new_basis_index] < 0 &&
            _constant_summands_of_equations[i] / _linear_coeffitients_of_equations[i][new_basis_index] > current_max) {
            result = i;
        }
    }
    return result;
}

void SimplexTableau::switch_basis_elements(VarID new_index, VarID old_index) {
    assert(_index_in_basis[new_index] == false && "new index must not already be in basis");
    assert(_index_in_basis[old_index] == true && "old index must stem from basis");

    // TODO: das minus hier könnte falsch sein...
    _constant_summands_of_equations[new_index] =
            -_constant_summands_of_equations[old_index] / _linear_coeffitients_of_equations[old_index][new_index];
    _constant_summands_of_equations[old_index] = 0;

    for (VarID i = 0; i < _linear_coeffitients_of_equations[new_index].size(); i++) {
        if (i == new_index) {
            _linear_coeffitients_of_equations[new_index][i] = 0;
        } else if (i == old_index) {
            _linear_coeffitients_of_equations[new_index][i] = -1 / _linear_coeffitients_of_equations[old_index][new_index];
        } else {
            _linear_coeffitients_of_equations[new_index][i] =
                    -_linear_coeffitients_of_equations[old_index][i] / _linear_coeffitients_of_equations[old_index][new_index];
        }
    }
    for (VarID i = 0; i < _linear_coeffitients_of_equations[new_index].size(); i++) {
        _linear_coeffitients_of_equations[old_index][i] = 0;
    }


    for(VarID i = 0; i < _linear_coeffitients_of_equations.size(); i++){
        if(i == new_index or i == old_index or not _index_in_basis[i]) continue;
        auto old_coeffitient = _linear_coeffitients_of_equations[i][new_index];
        for(VarID j = 0; j < _linear_coeffitients_of_equations[i].size(); i++){
            if(j == new_index){
                _linear_coeffitients_of_equations[i][j] = 0;
            } else {
                _linear_coeffitients_of_equations[i][j] += old_coeffitient *
                        _linear_coeffitients_of_equations[new_index][j];
            }
        }
    }

    _constant_term_of_target_equation += _linear_coeffitients_of_target_equation[new_index] *
            _constant_summands_of_equations[new_index];
    auto old_coeffitient = _linear_coeffitients_of_target_equation[new_index];
    for(VarID i = 0; i < _linear_coeffitients_of_target_equation.size(); i++){
        _linear_coeffitients_of_target_equation[i] += old_coeffitient * _linear_coeffitients_of_equations[new_index][i];
    }

    _index_in_basis[new_index] = true;
    _index_in_basis[old_index] = false;
}

Column SimplexTableau::extract_solution() const {
    return _constant_summands_of_equations;
}
