#include "variable_mod.h"
#include "utils.h"
#include <Rcpp.h>
/*.. _secRrefVariable:
.. highlight:: r

Variable
========

*/

/*.. class:: Variable

  Represents an AMPL decision variable. Note that, in case of a scalar
  variable, all the properties of the variable instance can be accessed
  through methods like :meth:`~.Variable.value`. The methods have the
  same name of the corresponding AMPL suffixes.
  See http://www.ampl.com/NEW/suffbuiltin.html for a list of the available
  suffixes.

  All these methods throw a TypeError if called for a non scalar
  objective and an RuntimeError if called on an entity which has been deleted
  in the underlying intepreter.

  To gain access to all the values in an entity (for all instances and all
  suffixes for that entities), see :meth:`~.Entity.getValues` and the
  :class:`DataFrame` class.

*/
RcppVariable::RcppVariable(ampl::Variable impl): RcppBasicEntity<ampl::VariableInstance>(impl), _impl(impl) { }

/*.. method:: Variable.value()

  Get the current value of this variable.

  :return: Value of the variable.
*/
double RcppVariable::value() const {
  return _impl.value();
}

/*.. method:: Variable.integrality()

  Get the integrality type for this variable.

  :return: Integrality type of the variable ("C" - continuous, "B" - binary, "I" - integer).
  :rtype: str
*/
std::string RcppVariable::integrality() const {
  ampl::var::Integrality typ = _impl.integrality();
  switch(typ){
    case ampl::var::CONTINUOUS: return "C"; break;
    case ampl::var::BINARY: return "B"; break;
    case ampl::var::INTEGER: return "I"; break;
    default: throw Rcpp::exception("Invalid integrality type.");
  }
}

/*.. method:: Variable.fix(value=NULL)

  Fix all instances of this variable to their current value, or to the specified value if provided.

  :param float value: The value the variable must be set to.

  :return: ``NULL``.
*/
void RcppVariable::fix() {
  _impl.fix();
}
void RcppVariable::fixDbl(double value) {
  _impl.fix(value);
}

/*.. method:: Variable.unfix()

  Unfix this variable instances.

  :return: ``NULL``.
*/
void RcppVariable::unfix() {
  _impl.unfix();
}

// **** SCALAR VARIABLES ****

/*.. method:: Variable.setValue()

  Set the current value of this variable (does not fix it),
  equivalent to the AMPL command `let`

  :param float value: Value to be set.

  :return: ``NULL``.
*/
void RcppVariable::setValue(double value) {
  _impl.setValue(value);
}

/*.. method:: Variable.astatus()

  Get the variable status (fixed, presolved, or substituted out).

  :return: Variable status.
  :rtype: str
*/
std::string RcppVariable::astatus() const {
  return _impl.astatus();
}

/*.. method:: Variable.defeqn()

  Get the index in `_con` of "defining constraint" used to substitute variable out.

  :return: Index of the defining constraint.
  :rtype: int
*/
int RcppVariable::defeqn() const {
  return _impl.defeqn();
}

/*.. method:: Variable.dual()

  Get the dual value on defining constraint of variable substituted out.

  :return: Dual value.
  :rtype: float
*/
double RcppVariable::dual() const {
  return _impl.dual();
}

/*.. method:: Variable.init()

  Get the current initial guess.

  :return: The initial guess.
  :rtype: float
*/
double RcppVariable::init() const {
  return _impl.init();
}

/*.. method:: Variable.init0()

  Get the original initial guess (set by `:=` or`default` or by a data statement)

  :return: The original initial guess.
  :rtype: float
*/
double RcppVariable::init0() const {
  return _impl.init0();
}

/*.. method:: Variable.lb()

  Returns the current lower bound. See :ref:`secVariableSuffixesNotes`.

  :return: The current lower bound.
  :rtype: float
*/
double RcppVariable::lb() const {
  return _impl.lb();
}

/*.. method:: Variable.ub()

  Returns the current upper bound. See :ref:`secVariableSuffixesNotes`.

  :return: The current upper bound.
  :rtype: float
*/
double RcppVariable::ub() const {
  return _impl.ub();
}

/*.. method:: Variable.lb0()

  Returns the initial lower bound, from the var declaration.

  :return: The intial lower bound.
  :rtype: float
*/
double RcppVariable::lb0() const {
  return _impl.lb0();
}

/*.. method:: Variable.ub0()

  Returns the initial upper bound, from the var declaration.

  :return: The intial upper bound.
  :rtype: float
*/
double RcppVariable::ub0() const {
  return _impl.ub0();
}

/*.. method:: Variable.lb1()

  Returns the weaker lower bound from AMPL's presolve phase.

  :return: The weaker lower bound.
  :rtype: float
*/
double RcppVariable::lb1() const {
  return _impl.lb1();
}

/*.. method:: Variable.ub1()

  Returns the weaker upper bound from AMPL's presolve phase.

  :return: The weaker upper bound.
  :rtype: float
*/
double RcppVariable::ub1() const {
  return _impl.ub1();
}

/*.. method:: Variable.lb2()

  Returns the stronger lower bound from AMPL's presolve phase.

  :return: The stronger lower bound.
  :rtype: float
*/
double RcppVariable::lb2() const {
  return _impl.lb2();
}

/*.. method:: Variable.ub2()

  Returns the stronger upper bound from AMPL's presolve phase.

  :return: The stronger upper bound.
  :rtype: float
*/
double RcppVariable::ub2() const {
  return _impl.ub2();
}

/*.. method:: Variable.lrc()

  Returns the reduced cost at lower bound.

  :return: The reduced cost at lower bound.
  :rtype: float
*/
double RcppVariable::lrc() const {
  return _impl.lrc();
}

/*.. method:: Variable.urc()

  Returns the reduced cost at upper bound.

  :return: The reduced cost at upper bound.
  :rtype: float
*/
double RcppVariable::urc() const {
  return _impl.urc();
}

/*.. method:: Variable.lslack()

  Returns the slack at lower bound (``val - lb``). See :ref:`secVariableSuffixesNotes`.

  :return: The slack at lower bound.
  :rtype: float
*/
double RcppVariable::lslack() const {
  return _impl.lslack();
}

/*.. method:: Variable.uslack()

  Returns the slack at upper bound (``ub - val``). See :ref:`secVariableSuffixesNotes`.

  :return: The slack at upper bound.
  :rtype: float
*/
double RcppVariable::uslack() const {
  return _impl.uslack();
}

/*.. method:: Variable.rc()

  Get the reduced cost (at the nearer bound).

  :return: The reduced cost.
  :rtype: float
*/
double RcppVariable::rc() const {
  return _impl.rc();
}

/*.. method:: Variable.slack()

  Returns the bound slack which is the lesser of lslack() and uslack(). See :ref:`secVariableSuffixesNotes`.

  :return: The smaller slack.
  :rtype: float
*/
double RcppVariable::slack() const {
  return _impl.slack();
}

/*.. method:: Variable.sstatus()

  Solver status (basis status of variable).

  :return: The basis status of the variable.
  :rtype: str
*/
std::string RcppVariable::sstatus() const {
  return _impl.sstatus();
}

/*.. method:: Variable.status()

  AMPL status if not `in`, otherwise solver status

  :return: The status of the variable.
  :rtype: str
*/
std::string RcppVariable::status() const {
  return _impl.status();
}

// *** RCPP_MODULE ***
RCPP_MODULE(variable_module){
    Rcpp::class_<RcppVariableEntity>( "VariableEntity" )
        .const_method( "[[", &RcppVariableEntity::get)
        ;
    Rcpp::class_<RcppVariable>( "Variable" )
        .derives<RcppVariableEntity>("VariableEntity")
        .method("value", &RcppVariable::value, "Get the current value of this variable")
        .method("integrality", &RcppVariable::integrality, "Get the integrality type for this variable")
        .method("fix", &RcppVariable::fix, "Fix all instances of this variable to their current value")
        .method("fix", &RcppVariable::fixDbl, "Fix all instances of this variable to the specified value")
        .method("unfix", &RcppVariable::unfix, "Unfix this variable instances")
        .method("setValue", &RcppVariable::setValue, "Set the current value of this variable")
        .method("astatus", &RcppVariable::astatus, "Get the variable status")
        .method("defeqn", &RcppVariable::defeqn, "Get the index of the defining constraint")
        .method("dual", &RcppVariable::dual, "Get the dual value on defining constraint")
        .method("init", &RcppVariable::init, "Get the current initial guess")
        .method("init0", &RcppVariable::init0, "Get the original initial guess")
        .method("lb", &RcppVariable::lb, "Returns the current lower bound")
        .method("ub", &RcppVariable::ub, "Returns the current upper bound")
        .method("lb0", &RcppVariable::lb0, "Returns the initial lower bound")
        .method("ub0", &RcppVariable::ub0, "Returns the initial upper bound")
        .method("lb1", &RcppVariable::lb1, "Returns the weaker lower bound")
        .method("ub1", &RcppVariable::ub1, "Returns the weaker upper bound")
        .method("lb2", &RcppVariable::lb2, "Returns the stronger lower bound")
        .method("ub2", &RcppVariable::ub2, "Returns the stronger upper bound")
        .method("lrc", &RcppVariable::lrc, "Returns the reduced cost at lower bound")
        .method("urc", &RcppVariable::urc, "Returns the reduced cost at upper bound")
        .method("lslack", &RcppVariable::lslack, "Returns the slack at lower bound")
        .method("uslack", &RcppVariable::uslack, "Returns the slack at upper bound")
        .method("rc", &RcppVariable::rc, "Get the reduced cost")
        .method("slack", &RcppVariable::slack, "Returns the smaller slack")
        .method("sstatus", &RcppVariable::sstatus, "Returns the solver status")
        .method("status", &RcppVariable::status, "Returns the AMPL status")
        ;
}
