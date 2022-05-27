//
// Created by jgier on 26.05.2022.
//

#ifndef SIMPLEX_SIMPLEXTABLEAU_H
#define SIMPLEX_SIMPLEXTABLEAU_H

#include <optional>
#include "typedef.h"
#include "linear_algebra.h"

class SimplexTableau {
public:
    SimplexTableau(LinearProgram const& linearProgram, std::vector<bool> basis);

    State iterate();

    [[nodiscard]] Column extract_solution() const;

private:

    [[nodiscard]] std::optional<VarID> blands_rule_new_basis_index() const;
    [[nodiscard]] std::optional<VarID> blands_rule_old_basis_index(VarID new_basis_index) const;

    void switch_basis_elements(VarID new_index, VarID old_index);



private:
    std::vector<bool> _index_in_basis;
    Column _constant_summands_of_equations;
    Matrix _linear_coeffitients_of_equations;
    Value _constant_term_of_target_equation;
    Row _linear_coeffitients_of_target_equation;
};


#endif //SIMPLEX_SIMPLEXTABLEAU_H
