#include "rcon_entity.h"
#include "utils.h"
#include <Rcpp.h>
/*.. _secRrefAMPL:
.. highlight:: r

Constraint
==========

*/

/*.. class:: Constraint

  This class represents an algebraic or logical constraint. In case the
  constraint is scalar, its values can be accessed via functions like
  :meth:`~.Constraint.body` and :meth:`~.Constraint.dual`.
  All the AMPL suffixes for constraints (see
  http://www.ampl.com/NEW/suffbuiltin.html)
  are available through methods of this class with the same name (and methods
  of ConstraintInstance for indexed constraints).

  Note that, since this class represents both algebraic and logical
  constraints, some suffixes might not be available for every entity.

  An error is thrown if one of such methods is called for
  a non-scalar constraint and if a method corresponding to a suffix which is
  not supported by the type of the constraint is called.
  An error is also thrown if any property of an entity which has been
  deleted from the underlying interpreter is accessed.

  To gain access to all the values in an entity (for all instances and all
  suffixes for that entities), see :meth:`~.Entity.getValues` and
  the :class:`DataFrame` class.
*/
RConstraintEntity::RConstraintEntity(ampl::Constraint impl): RBasicEntity<ampl::ConstraintInstance, RConstraintInstance>(impl), _impl(impl) { }

/*.. method:: Constraint.isLogical()

  Check if the constraint is a logical constraint. The available suffixes
  differ between logical and non logical constraints. See
  http://www.ampl.com/NEW/suffbuiltin.html for a list of the available
  suffixes for algebraic constraints. The suffixes available for logical
  constraints are marked on the method description by "Valid only for logical
  constraints".

  :return: ``TRUE`` if logical
*/
bool RConstraintEntity::isLogical() const {
  return _impl.isLogical();
}

/*.. method:: Constraint.drop()

  Drop all instances in this constraint entity, corresponding to the AMPL
  code: `drop constraintname;`
*/
void RConstraintEntity::drop() {
  return _impl.drop();
}

/*.. method:: Constraint.restore()

  Restore all instances in this constraint entity, corresponding to the
  AMPL code: `restore constraintname;`
*/
void RConstraintEntity::restore() {
  return _impl.restore();
}

/*.. method:: Constraint.body()

  Get the current value of the constraint's body.

  :return: The current value of the constraint's body.
*/
double RConstraintEntity::body() const {
  return _impl.body();
}


/*.. method:: Constraint.astatus()

  Get the current AMPL status (dropped, presolved, or substituted out).

  :return: The current AMPL status.
*/
std::string RConstraintEntity::astatus() const {
  return _impl.astatus();
}

/*.. method:: Constraint.defvar()

  Get the index in `_var` of "defined variable" substituted out by the constraint.

  :return: The index of the variable substituted out by the constraint.
*/
int RConstraintEntity::defvar() const {
  return _impl.defvar();
}

/*.. method:: Constraint.dinit()

  Get the current initial guess for the constraint's dual variable.

  :return: The current initial guess for the constraint's dual variable.
*/
double RConstraintEntity::dinit() const {
  return _impl.dinit();
}

/*.. method:: Constraint.dinit0()

  Get the original initial guess for the constraint's dual variable.

  :return: The original initial guess for the constraint's dual variable.
*/
double RConstraintEntity::dinit0() const {
  return _impl.dinit0();
}

/*.. method:: Constraint.dual()

  Get the current value of the constraint's dual variable.

  Note that dual values are often reset by the underlying AMPL interpreter by
  the presolve functionalities triggered by some methods.
  A possible workaround is to set the option `presolve;` to `false`
  (see :meth:`~.AMPL.setOption`).

  :return: The current value of the constraint's dual variable.
*/
double RConstraintEntity::dual() const {
  return _impl.dual();
}

/*.. method:: Constraint.lb()

  Get the current value of the constraint's lower bound.

  :return: The current value of the constraint's lower bound.
*/
double RConstraintEntity::lb() const {
  return _impl.lb();
}

/*.. method:: Constraint.ub()

  Get the current value of the constraint's upper bound.

  :return: The current value of the constraint's upper bound.
*/
double RConstraintEntity::ub() const {
  return _impl.ub();
}

/*.. method:: Constraint.lbs()

  Get the constraint lower bound sent to the solver (reflecting adjustment
  for fixed variables).

  :return: The constraint lower bound sent to the solver.
*/
double RConstraintEntity::lbs() const {
  return _impl.lbs();
}

/*.. method:: Constraint.ubs()

  Get the constraint upper bound sent to the solver (reflecting adjustment
  for fixed variables).

  :return: The constraint upper bound sent to the solver.
*/
double RConstraintEntity::ubs() const {
  return _impl.ubs();
}

/*.. method:: Constraint.ldual()

  Get the current dual value associated with the lower bound.

  :return: The current dual value associated with the lower bound.
*/
double RConstraintEntity::ldual() const {
  return _impl.ldual();
}

/*.. method:: Constraint.udual()

  Get the current dual value associated with the upper bounds

  :return: The current dual value associated with the upper bound.
*/
double RConstraintEntity::udual() const {
  return _impl.udual();
}


/*.. method:: Constraint.lslack()

  Get the slack at lower bound `body - lb`.

  :return: The slack at lower bound.
*/
double RConstraintEntity::lslack() const {
  return _impl.lslack();
}

/*.. method:: Constraint.uslack()

  Get the slack at upper bound `ub - body`

  :return: The slack at upper bound.
*/
double RConstraintEntity::uslack() const {
  return _impl.uslack();
}

/*.. method:: Constraint.slack()

  Constraint slack (the lesser of lslack and uslack).

  :return: The constraint slack.
*/
double RConstraintEntity::slack() const {
  return _impl.slack();
}

/*.. method:: Constraint.sstatus()

  Get the solver status (basis status of constraint's slack or artificial variable)

  :return: The solver status.
*/
std::string RConstraintEntity::sstatus() const {
  return _impl.sstatus();
}

/*.. method:: Constraint.status()

  Get the AMPL status if not `in`, otherwise solver status.

  :return: The AMPL status.
*/
std::string RConstraintEntity::status() const {
  return _impl.status();
}

/*.. method:: Constraint.setDual(dual)

  Set the value of the dual variable associated to this constraint (valid
  only if the constraint is scalar). Equivalent to the AMPL statement:

  `let c := dual;`

  Note that dual values are often reset by the underlying AMPL interpreter by
  the presolve functionalities triggered by some methods.
  A possible workaround is to set the option `presolve` to `false`
  (see :meth:`~.AMPL.setOption`).

  :param float dual: The value to be assigned to the dual variable.
*/
void RConstraintEntity::setDual(double dual) {
  return _impl.setDual(dual);
}

/*.. method:: Constraint.val()

  Get the AMPL val suffix. Valid only for logical constraints.

  :return: The val suffix.
*/
double RConstraintEntity::val() const {
  return _impl.val();
}

// *** RCPP_MODULE ***
RCPP_MODULE(rcon_entity){
  Rcpp::class_<RBasicEntity<ampl::ConstraintInstance, RConstraintInstance> >( "CEntity" )
    .const_method( "name", &RBasicEntity<ampl::ConstraintInstance, RConstraintInstance>::name)
    .const_method( "get", &RBasicEntity<ampl::ConstraintInstance, RConstraintInstance>::get)
    .const_method( "[[", &RBasicEntity<ampl::ConstraintInstance, RConstraintInstance>::get)
    ;
  Rcpp::class_<RConstraintEntity>("Constraint")
    .derives<RBasicEntity<ampl::ConstraintInstance, RConstraintInstance> >("CEntity")
    .method("isLogical", &RConstraintEntity::isLogical, "Check if the constraint is a logical constraint")
    .method("drop", &RConstraintEntity::drop, "Drop all instances in this constraint entity")
    .method("restore", &RConstraintEntity::restore, "Restore all instances in this constraint entity")
    .method("body", &RConstraintEntity::body, "Get the current value of the constraint's body")
    .method("astatus", &RConstraintEntity::astatus, "Get the current AMPL status")
    .method("defvar", &RConstraintEntity::defvar, "Get the index of variable substituted out by the constraint")
    .method("dinit", &RConstraintEntity::dinit, "Get the current initial guess for the constraint's dual variable")
    .method("dinit0", &RConstraintEntity::dinit0, "Get the original initial guess for the constraint's dual variable")
    .method("dual", &RConstraintEntity::dual, "Get the current value of the constraint's dual variable.")
    .method("lb", &RConstraintEntity::lb, "Get the current value of the constraint's lower bound")
    .method("ub", &RConstraintEntity::ub, "Get the current value of the constraint's upper bound")
    .method("lbs", &RConstraintEntity::lbs, "Get the constraint lower bound sent to the solver")
    .method("ubs", &RConstraintEntity::ubs, "Get the constraint upper bound sent to the solver")
    .method("ldual", &RConstraintEntity::ldual, "Get the current dual value associated with the lower bound")
    .method("udual", &RConstraintEntity::udual, "Get the current dual value associated with the upper bounds")
    .method("lslack", &RConstraintEntity::lslack, "Get the slack at lower bound")
    .method("uslack", &RConstraintEntity::uslack, "Get the slack at upper bound")
    .method("slack", &RConstraintEntity::slack, "Constraint slack")
    .method("sstatus", &RConstraintEntity::sstatus, "Get the solver status")
    .method("status", &RConstraintEntity::status, "Get the AMPL status")
    .method("setDual", &RConstraintEntity::setDual, "Set the value of the dual variable associated to this constraint")
    .method("val", &RConstraintEntity::val, "Get the AMPL val suffix.")
    ;
}
