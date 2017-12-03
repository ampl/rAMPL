#include "variable_mod.h"
#include "utils.h"
#include <Rcpp.h>
/*.. _secRrefVariable:
.. highlight:: r

Variable
========

*/

// Fix ld error: undefined symbol
template class RcppVariable<ampl::Variable>;

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
template <class T>
RcppVariable<T>::RcppVariable(T impl): _impl(impl) { }

/*.. method:: Variable.value()

  Get the current value of this variable.

  :return: Value of the variable.
*/
template <class T>
double RcppVariable<T>::value() const {
  return _impl.value();
}

/*.. method:: Variable.integrality()

  Get the integrality type for this variable.

  :return: Integrality type of the variable ("C" - continuous, "B" - binary, "I" - integer).
  :rtype: str
*/
template <class T>
std::string RcppVariable<T>::integrality() const {
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
template <class T>
void RcppVariable<T>::fix() {
  _impl.fix();
}
template <class T>
void RcppVariable<T>::fixDbl(double value) {
  _impl.fix(value);
}

/*.. method:: Variable.unfix()

  Unfix this variable instances.

  :return: ``NULL``.
*/
template <class T>
void RcppVariable<T>::unfix() {
  _impl.unfix();
}

// **** SCALAR VARIABLES ****

/*.. method:: Variable.setValue()

  Set the current value of this variable (does not fix it),
  equivalent to the AMPL command `let`

  :param float value: Value to be set.

  :return: ``NULL``.
*/
template <class T>
void RcppVariable<T>::setValue(double value) {
  _impl.setValue(value);
}

/*.. method:: Variable.astatus()

  Get the variable status (fixed, presolved, or substituted out).

  :return: Variable status.
  :rtype: str
*/
template <class T>
std::string RcppVariable<T>::astatus() const {
  return _impl.astatus();
}

/*.. method:: Variable.defeqn()

  Get the index in `_con` of "defining constraint" used to substitute variable out.

  :return: Index of the defining constraint.
  :rtype: int
*/
template <class T>
int RcppVariable<T>::defeqn() const {
  return _impl.defeqn();
}

/*.. method:: Variable.dual()

  Get the dual value on defining constraint of variable substituted out.

  :return: Dual value.
  :rtype: float
*/
template <class T>
double RcppVariable<T>::dual() const {
  return _impl.dual();
}

/*.. method:: Variable.init()

  Get the current initial guess.

  :return: The initial guess.
  :rtype: float
*/
template <class T>
double RcppVariable<T>::init() const {
  return _impl.init();
}

/*.. method:: Variable.init0()

  Get the original initial guess (set by `:=` or`default` or by a data statement)

  :return: The original initial guess.
  :rtype: float
*/
template <class T>
double RcppVariable<T>::init0() const {
  return _impl.init0();
}

/*.. method:: Variable.lb()

  Returns the current lower bound. See :ref:`secVariableSuffixesNotes`.

  :return: The current lower bound.
  :rtype: float
*/
template <class T>
double RcppVariable<T>::lb() const {
  return _impl.lb();
}

/*.. method:: Variable.ub()

  Returns the current upper bound. See :ref:`secVariableSuffixesNotes`.

  :return: The current upper bound.
  :rtype: float
*/
template <class T>
double RcppVariable<T>::ub() const {
  return _impl.ub();
}

/*.. method:: Variable.lb0()

  Returns the initial lower bound, from the var declaration.

  :return: The intial lower bound.
  :rtype: float
*/
template <class T>
double RcppVariable<T>::lb0() const {
  return _impl.lb0();
}

/*.. method:: Variable.ub0()

  Returns the initial upper bound, from the var declaration.

  :return: The intial upper bound.
  :rtype: float
*/
template <class T>
double RcppVariable<T>::ub0() const {
  return _impl.ub0();
}

/*.. method:: Variable.lb1()

  Returns the weaker lower bound from AMPL's presolve phase.

  :return: The weaker lower bound.
  :rtype: float
*/
template <class T>
double RcppVariable<T>::lb1() const {
  return _impl.lb1();
}

/*.. method:: Variable.ub1()

  Returns the weaker upper bound from AMPL's presolve phase.

  :return: The weaker upper bound.
  :rtype: float
*/
template <class T>
double RcppVariable<T>::ub1() const {
  return _impl.ub1();
}

/*.. method:: Variable.lb2()

  Returns the stronger lower bound from AMPL's presolve phase.

  :return: The stronger lower bound.
  :rtype: float
*/
template <class T>
double RcppVariable<T>::lb2() const {
  return _impl.lb2();
}

/*.. method:: Variable.ub2()

  Returns the stronger upper bound from AMPL's presolve phase.

  :return: The stronger upper bound.
  :rtype: float
*/
template <class T>
double RcppVariable<T>::ub2() const {
  return _impl.ub2();
}

/*.. method:: Variable.lrc()

  Returns the reduced cost at lower bound.

  :return: The reduced cost at lower bound.
  :rtype: float
*/
template <class T>
double RcppVariable<T>::lrc() const {
  return _impl.lrc();
}

/*.. method:: Variable.urc()

  Returns the reduced cost at upper bound.

  :return: The reduced cost at upper bound.
  :rtype: float
*/
template <class T>
double RcppVariable<T>::urc() const {
  return _impl.urc();
}

/*.. method:: Variable.lslack()

  Returns the slack at lower bound (``val - lb``). See :ref:`secVariableSuffixesNotes`.

  :return: The slack at lower bound.
  :rtype: float
*/
template <class T>
double RcppVariable<T>::lslack() const {
  return _impl.lslack();
}

/*.. method:: Variable.uslack()

  Returns the slack at upper bound (``ub - val``). See :ref:`secVariableSuffixesNotes`.

  :return: The slack at upper bound.
  :rtype: float
*/
template <class T>
double RcppVariable<T>::uslack() const {
  return _impl.uslack();
}

/*.. method:: Variable.rc()

  Get the reduced cost (at the nearer bound).

  :return: The reduced cost.
  :rtype: float
*/
template <class T>
double RcppVariable<T>::rc() const {
  return _impl.rc();
}

/*.. method:: Variable.slack()

  Returns the bound slack which is the lesser of lslack() and uslack(). See :ref:`secVariableSuffixesNotes`.

  :return: The smaller slack.
  :rtype: float
*/
template <class T>
double RcppVariable<T>::slack() const {
  return _impl.slack();
}

/*.. method:: Variable.sstatus()

  Solver status (basis status of variable).

  :return: The basis status of the variable.
  :rtype: str
*/
template <class T>
std::string RcppVariable<T>::sstatus() const {
  return _impl.sstatus();
}

/*.. method:: Variable.status()

  AMPL status if not `in`, otherwise solver status

  :return: The status of the variable.
  :rtype: str
*/
template <class T>
std::string RcppVariable<T>::status() const {
  return _impl.status();
}

/*template <class T>
RcppVariable RcppVariable<T>::get(Rcpp::List index) const {
  int p = 0;
  ampl::Tuple tuple(index.size());
  for(Rcpp::List::iterator it = index.begin(); it != index.end(); it++) {
    switch(TYPEOF(*it)) {
      case REALSXP:
        tuple[p++] = ampl::Variant(Rcpp::as<double>(*it));
        break;
      case INTSXP:
        tuple[p++] = ampl::Variant(Rcpp::as<int>(*it));
        break;
      case STRSXP:
        tuple[p++] = ampl::Variant(Rcpp::as<std::string>(*it));
        break;
	    default:
        Rcpp::stop("only accepts lists containing numbers and strings");
    }
  }
  return RcppVariable<ampl::VariableInstance>(_impl.get(tuple));
}*/

// *** RCPP_MODULE ***
RCPP_MODULE(variable_module){
    Rcpp::class_<RcppVariableEntity>( "Variable" )
        .method("value", &RcppVariableEntity::value, "Get the current value of this variable")
        .method("integrality", &RcppVariableEntity::integrality, "Get the integrality type for this variable")
        .method("fix", &RcppVariableEntity::fix, "Fix all instances of this variable to their current value")
        .method("fix", &RcppVariableEntity::fixDbl, "Fix all instances of this variable to the specified value")
        .method("unfix", &RcppVariableEntity::unfix, "Unfix this variable instances")
        .method("setValue", &RcppVariableEntity::setValue, "Set the current value of this variable")
        .method("astatus", &RcppVariableEntity::astatus, "Get the variable status")
        .method("defeqn", &RcppVariableEntity::defeqn, "Get the index of the defining constraint")
        .method("dual", &RcppVariableEntity::dual, "Get the dual value on defining constraint")
        .method("init", &RcppVariableEntity::init, "Get the current initial guess")
        .method("init0", &RcppVariableEntity::init0, "Get the original initial guess")
        .method("lb", &RcppVariableEntity::lb, "Returns the current lower bound")
        .method("ub", &RcppVariableEntity::ub, "Returns the current upper bound")
        .method("lb0", &RcppVariableEntity::lb0, "Returns the initial lower bound")
        .method("ub0", &RcppVariableEntity::ub0, "Returns the initial upper bound")
        .method("lb1", &RcppVariableEntity::lb1, "Returns the weaker lower bound")
        .method("ub1", &RcppVariableEntity::ub1, "Returns the weaker upper bound")
        .method("lb2", &RcppVariableEntity::lb2, "Returns the stronger lower bound")
        .method("ub2", &RcppVariableEntity::ub2, "Returns the stronger upper bound")
        .method("lrc", &RcppVariableEntity::lrc, "Returns the reduced cost at lower bound")
        .method("urc", &RcppVariableEntity::urc, "Returns the reduced cost at upper bound")
        .method("lslack", &RcppVariableEntity::lslack, "Returns the slack at lower bound")
        .method("uslack", &RcppVariableEntity::uslack, "Returns the slack at upper bound")
        .method("rc", &RcppVariableEntity::rc, "Get the reduced cost")
        .method("slack", &RcppVariableEntity::slack, "Returns the smaller slack")
        .method("sstatus", &RcppVariableEntity::sstatus, "Returns the solver status")
        .method("status", &RcppVariableEntity::status, "Returns the AMPL status")
        //.const_method( "[[", &RcppVariableEntity::get)
        ;
}
