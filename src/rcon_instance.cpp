#include "rcon_entity.h"
#include "utils.h"
#include <Rcpp.h>
/*.. _secRrefConInstance:
.. highlight:: r

ConstraintInstance
==================

*/

/*.. class:: ConstraintInstance

  This class represent an instance of a constraint.

  In general, all AMPL suffixes for a constraint are available through methods
  with the same name in this class. See http://www.ampl.com/NEW/suffbuiltin.html
  for a list of the available suffixes.

  Note that, since this class represents instances of both algebraic and logical
  constraints, some suffixes might not be available for every instance.
  If a wrong suffix for the specific class
  of constraint is accessed, an error is thrown.

  All the accessors in this class throw an error if the instance
  has been deleted in the underlying AMPL interpreter.
*/
RConstraintInstance::RConstraintInstance(ampl::ConstraintInstance impl): _impl(impl) { }

/*.. method:: ConstraintInstance.drop()

  Drop this constraint instance, corresponding to the AMPL
  code: `drop constraintname;`
*/
void RConstraintInstance::drop() {
  return _impl.drop();
}

/*.. method:: ConstraintInstance.restore()

  Restore this constraint instance, corresponding to the
  AMPL code: `restore constraintname;`
*/
void RConstraintInstance::restore() {
  return _impl.restore();
}

/*.. method:: ConstraintInstance.body()

  Get the current value of the constraint's body.

  :return: The current value of the constraint's body.
*/
double RConstraintInstance::body() const {
  return _impl.body();
}

/*.. method:: ConstraintInstance.astatus()

  Get the current AMPL status (dropped, presolved, or substituted out).

  :return: The current AMPL status.
*/
std::string RConstraintInstance::astatus() const {
  return _impl.astatus();
}

/*.. method:: ConstraintInstance.defvar()

  Get the index in `_var` of "defined variable" substituted out by the constraint.

  :return: The index of the variable substituted out by the constraint.
*/
int RConstraintInstance::defvar() const {
  return _impl.defvar();
}

/*.. method:: ConstraintInstance.dinit()

  Get the current initial guess for the constraint's dual variable.

  :return: The current initial guess for the constraint's dual variable.
*/
double RConstraintInstance::dinit() const {
  return _impl.dinit();
}

/*.. method:: ConstraintInstance.dinit0()

  Get the original initial guess for the constraint's dual variable.

  :return: The original initial guess for the constraint's dual variable.
*/
double RConstraintInstance::dinit0() const {
  return _impl.dinit0();
}

/*.. method:: ConstraintInstance.dual()

  Get the current value of the constraint's dual variable.

  Note that dual values are often reset by the underlying AMPL interpreter by
  the presolve functionalities triggered by some methods.
  A possible workaround is to set the option `presolve;` to `false`
  (see :meth:`~.AMPL.setOption`).

  :return: The current value of the constraint's dual variable.
*/
double RConstraintInstance::dual() const {
  return _impl.dual();
}

/*.. method:: ConstraintInstance.lb()

  Get the current value of the constraint's lower bound.

  :return: The current value of the constraint's lower bound.
*/
double RConstraintInstance::lb() const {
  return _impl.lb();
}

/*.. method:: ConstraintInstance.ub()

  Get the current value of the constraint's upper bound.

  :return: The current value of the constraint's upper bound.
*/
double RConstraintInstance::ub() const {
  return _impl.ub();
}

/*.. method:: ConstraintInstance.lbs()

  Get the constraint lower bound sent to the solver (reflecting adjustment
  for fixed variables).

  :return: The constraint lower bound sent to the solver.
*/
double RConstraintInstance::lbs() const {
  return _impl.lbs();
}

/*.. method:: ConstraintInstance.ubs()

  Get the constraint upper bound sent to the solver (reflecting adjustment
  for fixed variables).

  :return: The constraint upper bound sent to the solver.
*/
double RConstraintInstance::ubs() const {
  return _impl.ubs();
}

/*.. method:: ConstraintInstance.ldual()

  Get the current dual value associated with the lower bound.

  :return: The current dual value associated with the lower bound.
*/
double RConstraintInstance::ldual() const {
  return _impl.ldual();
}

/*.. method:: ConstraintInstance.udual()

  Get the current dual value associated with the upper bounds

  :return: The current dual value associated with the upper bound.
*/
double RConstraintInstance::udual() const {
  return _impl.udual();
}


/*.. method:: ConstraintInstance.lslack()

  Get the slack at lower bound `body - lb`.

  :return: The slack at lower bound.
*/
double RConstraintInstance::lslack() const {
  return _impl.lslack();
}

/*.. method:: ConstraintInstance.uslack()

  Get the slack at upper bound `ub - body`

  :return: The slack at upper bound.
*/
double RConstraintInstance::uslack() const {
  return _impl.uslack();
}

/*.. method:: ConstraintInstance.slack()

  Constraint slack (the lesser of lslack and uslack).

  :return: The constraint slack.
*/
double RConstraintInstance::slack() const {
  return _impl.slack();
}

/*.. method:: ConstraintInstance.sstatus()

  Get the solver status (basis status of constraint's slack or artificial variable)

  :return: The solver status.
*/
std::string RConstraintInstance::sstatus() const {
  return _impl.sstatus();
}

/*.. method:: ConstraintInstance.status()

  Get the AMPL status if not `in`, otherwise solver status.

  :return: The AMPL status.
*/
std::string RConstraintInstance::status() const {
  return _impl.status();
}

/*.. method:: ConstraintInstance.setDual(dual)

  Set the value of the dual variable associated to this constraint (valid
  only if the constraint is scalar). Equivalent to the AMPL statement:

  `let c := dual;`

  Note that dual values are often reset by the underlying AMPL interpreter by
  the presolve functionalities triggered by some methods.
  A possible workaround is to set the option `presolve` to `false`
  (see :meth:`~.AMPL.setOption`).

  :param float dual: The value to be assigned to the dual variable.
*/
void RConstraintInstance::setDual(double dual) {
  return _impl.setDual(dual);
}

/*.. method:: ConstraintInstance.val()

  Get the AMPL val suffix. Valid only for logical constraints.

  :return: The val suffix.
*/
double RConstraintInstance::val() const {
  return _impl.val();
}

// *** RCPP_MODULE ***
RCPP_MODULE(rcon_instance){
  Rcpp::class_<RConstraintInstance>( "ConstraintInstance" )
    .method("drop", &RConstraintInstance::drop, "Drop this constraint instance")
    .method("restore", &RConstraintInstance::restore, "Restore this constraint instance")
    .method("body", &RConstraintInstance::body, "Get the current value of the constraint's body")
    .method("astatus", &RConstraintInstance::astatus, "Get the current AMPL status")
    .method("defvar", &RConstraintInstance::defvar, "Get the index of variable substituted out by the constraint")
    .method("dinit", &RConstraintInstance::dinit, "Get the current initial guess for the constraint's dual variable")
    .method("dinit0", &RConstraintInstance::dinit0, "Get the original initial guess for the constraint's dual variable")
    .method("dual", &RConstraintInstance::dual, "Get the current value of the constraint's dual variable.")
    .method("lb", &RConstraintInstance::lb, "Get the current value of the constraint's lower bound")
    .method("ub", &RConstraintInstance::ub, "Get the current value of the constraint's upper bound")
    .method("lbs", &RConstraintInstance::lbs, "Get the constraint lower bound sent to the solver")
    .method("ubs", &RConstraintInstance::ubs, "Get the constraint upper bound sent to the solver")
    .method("ldual", &RConstraintInstance::ldual, "Get the current dual value associated with the lower bound")
    .method("udual", &RConstraintInstance::udual, "Get the current dual value associated with the upper bounds")
    .method("lslack", &RConstraintInstance::lslack, "Get the slack at lower bound")
    .method("uslack", &RConstraintInstance::uslack, "Get the slack at upper bound")
    .method("slack", &RConstraintInstance::slack, "Constraint slack")
    .method("sstatus", &RConstraintInstance::sstatus, "Get the solver status")
    .method("status", &RConstraintInstance::status, "Get the AMPL status")
    .method("setDual", &RConstraintInstance::setDual, "Set the value of the dual variable associated to this constraint")
    .method("val", &RConstraintInstance::val, "Get the AMPL val suffix.")
    ;
}
