#include "variable_mod.h"
#include "utils.h"
#include <Rcpp.h>
/*.. _secRrefAMPL:
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
RcppVariable::RcppVariable(ampl::Variable impl): _impl(impl) { }

/*.. method:: Variable.value()

  Get the current value of this variable.

  :return: Value of the variable.
*/
double RcppVariable::value() const {
  return _impl.value();
}

// *** RCPP_MODULE ***
RCPP_MODULE(variable_module){
    Rcpp::class_<RcppVariable>( "Variable" )
        .method("value", &RcppVariable::value, "Get the current value of this variable")
        ;
}
