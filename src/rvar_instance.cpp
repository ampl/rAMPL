#include "rvar_instance.h"
#include "utils.h"
#include <Rcpp.h>
/*.. _secRrefVarInstance:
.. highlight:: r

VariableInstance
================

*/

/*.. class:: VariableInstance

  A decision variable instance. Each member of this class belongs to a single
  Variable.
  Note that accessors available here are replicated at Variable level for ease
  of use when dealing with scalar variables.

  All AMPL suffixes for an algebraic variable are available through methods with
  the same name in this class. See http://www.ampl.com/NEW/suffbuiltin.html
  for a list of the available suffixes.

  All the accessors in this class throw an error if the instance
  has been deleted in the underlying AMPL interpreter.
*/
RVariableInstance::RVariableInstance(ampl::VariableInstance impl): _impl(impl) { }

/*.. method:: VariableInstance.name()

  Returns the name of this instance.

  :return: Name of the instance.
*/
std::string RVariableInstance::name() const {
  return _impl.name();
}

/*.. method:: VariableInstance.toString()

  Returns a string representation of this instance.

  :return: String representation of this instance.
*/
std::string RVariableInstance::toString() const {
  return _impl.toString();
}

/*.. method:: VariableInstance.value()

  Get the current value of this variable.

  :return: Value of the variable.
*/
double RVariableInstance::value() const {
  return _impl.value();
}

/*.. method:: VariableInstance.fix(value=NULL)

  Fix all instances of this variable to their current value, or to the specified value if provided.

  :param float value: The value the variable must be set to.

  :return: ``NULL``.
*/
void RVariableInstance::fix() {
  _impl.fix();
}
void RVariableInstance::fixDbl(double value) {
  _impl.fix(value);
}

/*.. method:: VariableInstance.unfix()

  Unfix this variable instances.

  :return: ``NULL``.
*/
void RVariableInstance::unfix() {
  _impl.unfix();
}

// **** SCALAR VARIABLES ****

/*.. method:: VariableInstance.setValue()

  Set the current value of this variable (does not fix it),
  equivalent to the AMPL command `let`

  :param float value: Value to be set.

  :return: ``NULL``.
*/
void RVariableInstance::setValue(double value) {
  _impl.setValue(value);
}

/*.. method:: VariableInstance.astatus()

  Get the variable status (fixed, presolved, or substituted out).

  :return: Variable status.
  :rtype: str
*/
std::string RVariableInstance::astatus() const {
  return _impl.astatus();
}

/*.. method:: VariableInstance.defeqn()

  Get the index in `_con` of "defining constraint" used to substitute variable out.

  :return: Index of the defining constraint.
  :rtype: int
*/
int RVariableInstance::defeqn() const {
  return _impl.defeqn();
}

/*.. method:: VariableInstance.dual()

  Get the dual value on defining constraint of variable substituted out.

  :return: Dual value.
  :rtype: float
*/
double RVariableInstance::dual() const {
  return _impl.dual();
}

/*.. method:: VariableInstance.init()

  Get the current initial guess.

  :return: The initial guess.
  :rtype: float
*/
double RVariableInstance::init() const {
  return _impl.init();
}

/*.. method:: VariableInstance.init0()

  Get the original initial guess (set by `:=` or`default` or by a data statement)

  :return: The original initial guess.
  :rtype: float
*/
double RVariableInstance::init0() const {
  return _impl.init0();
}

/*.. method:: VariableInstance.lb()

  Returns the current lower bound. See :ref:`secVariableSuffixesNotes`.

  :return: The current lower bound.
  :rtype: float
*/
double RVariableInstance::lb() const {
  return _impl.lb();
}

/*.. method:: VariableInstance.ub()

  Returns the current upper bound. See :ref:`secVariableSuffixesNotes`.

  :return: The current upper bound.
  :rtype: float
*/
double RVariableInstance::ub() const {
  return _impl.ub();
}

/*.. method:: VariableInstance.lb0()

  Returns the initial lower bound, from the var declaration.

  :return: The intial lower bound.
  :rtype: float
*/
double RVariableInstance::lb0() const {
  return _impl.lb0();
}

/*.. method:: VariableInstance.ub0()

  Returns the initial upper bound, from the var declaration.

  :return: The intial upper bound.
  :rtype: float
*/
double RVariableInstance::ub0() const {
  return _impl.ub0();
}

/*.. method:: VariableInstance.lb1()

  Returns the weaker lower bound from AMPL's presolve phase.

  :return: The weaker lower bound.
  :rtype: float
*/
double RVariableInstance::lb1() const {
  return _impl.lb1();
}

/*.. method:: VariableInstance.ub1()

  Returns the weaker upper bound from AMPL's presolve phase.

  :return: The weaker upper bound.
  :rtype: float
*/
double RVariableInstance::ub1() const {
  return _impl.ub1();
}

/*.. method:: VariableInstance.lb2()

  Returns the stronger lower bound from AMPL's presolve phase.

  :return: The stronger lower bound.
  :rtype: float
*/
double RVariableInstance::lb2() const {
  return _impl.lb2();
}

/*.. method:: VariableInstance.ub2()

  Returns the stronger upper bound from AMPL's presolve phase.

  :return: The stronger upper bound.
  :rtype: float
*/
double RVariableInstance::ub2() const {
  return _impl.ub2();
}

/*.. method:: VariableInstance.lrc()

  Returns the reduced cost at lower bound.

  :return: The reduced cost at lower bound.
  :rtype: float
*/
double RVariableInstance::lrc() const {
  return _impl.lrc();
}

/*.. method:: VariableInstance.urc()

  Returns the reduced cost at upper bound.

  :return: The reduced cost at upper bound.
  :rtype: float
*/
double RVariableInstance::urc() const {
  return _impl.urc();
}

/*.. method:: VariableInstance.lslack()

  Returns the slack at lower bound (``val - lb``). See :ref:`secVariableSuffixesNotes`.

  :return: The slack at lower bound.
  :rtype: float
*/
double RVariableInstance::lslack() const {
  return _impl.lslack();
}

/*.. method:: VariableInstance.uslack()

  Returns the slack at upper bound (``ub - val``). See :ref:`secVariableSuffixesNotes`.

  :return: The slack at upper bound.
  :rtype: float
*/
double RVariableInstance::uslack() const {
  return _impl.uslack();
}

/*.. method:: VariableInstance.rc()

  Get the reduced cost (at the nearer bound).

  :return: The reduced cost.
  :rtype: float
*/
double RVariableInstance::rc() const {
  return _impl.rc();
}

/*.. method:: VariableInstance.slack()

  Returns the bound slack which is the lesser of lslack() and uslack(). See :ref:`secVariableSuffixesNotes`.

  :return: The smaller slack.
  :rtype: float
*/
double RVariableInstance::slack() const {
  return _impl.slack();
}

/*.. method:: VariableInstance.sstatus()

  Solver status (basis status of variable).

  :return: The basis status of the variable.
  :rtype: str
*/
std::string RVariableInstance::sstatus() const {
  return _impl.sstatus();
}

/*.. method:: VariableInstance.status()

  AMPL status if not `in`, otherwise solver status

  :return: The status of the variable.
  :rtype: str
*/
std::string RVariableInstance::status() const {
  return _impl.status();
}

// *** RCPP_MODULE ***
RCPP_MODULE(rvar_instance){
  Rcpp::class_<RVariableInstance>("VariableInstance")
    .method("name", &RVariableInstance::name)
    .method("toString", &RVariableInstance::toString)
    .method("value", &RVariableInstance::value, "Get the current value of this variable")
    //.method("integrality", &RVariableInstance::integrality, "Get the integrality type for this variable")
    .method("fix", &RVariableInstance::fix, "Fix all instances of this variable to their current value")
    .method("fix", &RVariableInstance::fixDbl, "Fix all instances of this variable to the specified value")
    .method("unfix", &RVariableInstance::unfix, "Unfix this variable instances")
    .method("setValue", &RVariableInstance::setValue, "Set the current value of this variable")
    .method("astatus", &RVariableInstance::astatus, "Get the variable status")
    .method("defeqn", &RVariableInstance::defeqn, "Get the index of the defining constraint")
    .method("dual", &RVariableInstance::dual, "Get the dual value on defining constraint")
    .method("init", &RVariableInstance::init, "Get the current initial guess")
    .method("init0", &RVariableInstance::init0, "Get the original initial guess")
    .method("lb", &RVariableInstance::lb, "Returns the current lower bound")
    .method("ub", &RVariableInstance::ub, "Returns the current upper bound")
    .method("lb0", &RVariableInstance::lb0, "Returns the initial lower bound")
    .method("ub0", &RVariableInstance::ub0, "Returns the initial upper bound")
    .method("lb1", &RVariableInstance::lb1, "Returns the weaker lower bound")
    .method("ub1", &RVariableInstance::ub1, "Returns the weaker upper bound")
    .method("lb2", &RVariableInstance::lb2, "Returns the stronger lower bound")
    .method("ub2", &RVariableInstance::ub2, "Returns the stronger upper bound")
    .method("lrc", &RVariableInstance::lrc, "Returns the reduced cost at lower bound")
    .method("urc", &RVariableInstance::urc, "Returns the reduced cost at upper bound")
    .method("lslack", &RVariableInstance::lslack, "Returns the slack at lower bound")
    .method("uslack", &RVariableInstance::uslack, "Returns the slack at upper bound")
    .method("rc", &RVariableInstance::rc, "Get the reduced cost")
    .method("slack", &RVariableInstance::slack, "Returns the smaller slack")
    .method("sstatus", &RVariableInstance::sstatus, "Returns the solver status")
    .method("status", &RVariableInstance::status, "Returns the AMPL status")
    ;
}
