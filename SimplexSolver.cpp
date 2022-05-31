//
// Created by jgier on 25.05.2022.
//

#include <cassert>
#include "SimplexSolver.h"
#include "LinearProgram.h"


SimplexSolver::SimplexSolver(LinearProgram &linear_program) : _linear_program(linear_program) {
    _linear_program.make_constraints_vector_non_negative();
}

State SimplexSolver::solve() {
    SimplexTableau tableau = create_extended_simplex_tableau();
    State state;
    tableau.print();
    while ((state = tableau.iterate()) == SOLVED) {
        tableau.print();
    }
    assert(state == OPTIMAL && "The auxiliary simplex must reach an optimal solution");
    if (not tableau.crop_tableau(_linear_program.num_equations())) {
        return INFEASIBLE;
    }
    tableau.set_target_equation(0, _linear_program.target_vector());
    tableau.print();
    while ((state = tableau.iterate()) == SOLVED) {
        tableau.print();
    }
    _linear_program.set_solution(tableau.extract_solution());
    return state;
}

SimplexTableau SimplexSolver::create_extended_simplex_tableau() const {

    /*
     * The simplex tableau is created by
     *  1. taking the data of the linear program,
     *  2. adding the new variables to the eqations and
     *  3. rearranging the equations, such that they are in terms of the slack-variables.
     * This rearrangement causes most added values and vectors to be negated.
     */

    VarID num_original_variables = _linear_program.num_variables();
    VarID num_slack_variables = _linear_program.num_equations();

    std::vector<bool> index_in_basis(num_original_variables, false);
    for (VarID i = 0; i < num_slack_variables; i++) {
        index_in_basis.push_back(true);
    }

    Column constant_summands_of_equations(num_original_variables, 0);
    for (VarID i = 0; i < num_slack_variables; i++) {
        constant_summands_of_equations.push_back(_linear_program.constraints_vector()[i]);
    }

    (negate(_linear_program.constraints_vector()));
    Matrix linear_coeffitients_of_equations;
    for (VarID i = 0; i < num_original_variables; i++) {
        linear_coeffitients_of_equations.push_back(Column(num_original_variables + num_slack_variables));
    }
    for (VarID i = 0; i < num_slack_variables; i++) {
        linear_coeffitients_of_equations.push_back(negate(_linear_program.constraints_matrix()[i]));
        for (VarID j = 0; j < num_slack_variables; j++) {
            linear_coeffitients_of_equations.back().push_back(0);
        }
    }

    Value constant_term_of_target_equation = 0;
    Row linear_coeffitients_of_target_equation(num_original_variables + num_slack_variables, 0);
    for (VarID i = num_original_variables; i < num_slack_variables + num_original_variables; i++) {
        add(linear_coeffitients_of_target_equation, multiply(linear_coeffitients_of_equations[i], -1));
        constant_term_of_target_equation -= constant_summands_of_equations[i];
    }

    return {index_in_basis, constant_summands_of_equations, linear_coeffitients_of_equations,
            constant_term_of_target_equation, linear_coeffitients_of_target_equation};
}

