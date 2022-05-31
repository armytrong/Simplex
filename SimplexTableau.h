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
    SimplexTableau(std::vector<bool> index_in_basis, Column constant_summands_of_equations,
                   Matrix linear_coeffitients_of_equations, Value constant_term_of_target_equation,
                   Row linear_coeffitients_of_target_equation);

    /*
     * This function removes a predifined number of variables from the tableau. As it does this, it swappes eventual
     * basis elements from the removed indices to the remaining indices.
     */
    bool crop_tableau(VarID num_slack_variables_to_crop);

    // Advance the simplex tableau by one step.
    State iterate();

    // Change the internal target equation. Needed after cropping, when a fesible basis has been calculated.
    void set_target_equation(Value constant_term, Row linear_coeffitients);

    [[nodiscard]] Column extract_solution() const;

    void print();

private:

    /*
     * Bland's rule chooses the first index with a positive coeffitient in the target function as the new basis index
     * and chooses the first basis element, where the new variable value is maximized
     */
    [[nodiscard]] std::optional<VarID> blands_rule_new_basis_index() const;
    [[nodiscard]] std::optional<VarID> blands_rule_old_basis_index(VarID new_basis_index) const;

    /*
     * This method does the heavy lifting. It computes the change of the simplex tablea when two basis elements are
     * swapped, implementing a lot of calculations for rearranging the equations in the simplex tableau.
     */
    void switch_basis_elements(VarID new_index, VarID old_index);


private:

    /*
     *  This implementation of the simplex tableau always holds an equation for each variable, regardless weather it
     *  is in the basis or not. All non-basis-equations are just 0.
     *  The basis itself is saved as a boolean vector.
     */

    std::vector<bool> _index_in_basis;
    Column _constant_summands_of_equations;
    Matrix _linear_coeffitients_of_equations;
    Value _constant_term_of_target_equation;
    Row _linear_coeffitients_of_target_equation;
};


#endif //SIMPLEX_SIMPLEXTABLEAU_H
