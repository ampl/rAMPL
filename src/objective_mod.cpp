#include "objective_mod.h"
#include "utils.h"
#include <Rcpp.h>
/*.. _secRrefAMPL:
.. highlight:: r

Objective
=========

*/

/*.. class:: Objective

  Represents an AMPL objective. Note that, in case of a scalar objective, all
  the properties (corresponding to AMPL suffixes) of the objective instance
  can be accessed through methods like :meth:`~.Objective.value`.
  The methods have the same name of the corresponding AMPL suffixes.
  See http://www.ampl.com/NEW/suffbuiltin.html for a list of the available
  suffixes.

  All these methods throw a TypeError if called for a non scalar
  objective and an RuntimeError if called on an entity which has been deleted
  in the underlying intepreter.

  To gain access to all the values in an entity (for all instances and all
  suffixes for that entities), see :meth:`~.Entity.getValues` and the
  :class:`DataFrame` class.
*/
RcppObjective::RcppObjective(ampl::Objective impl): _impl(impl) { }

/*.. method:: Objective.value()

  Get the value of the objective instance

  :return: Value of the objective.
*/
double RcppObjective::value() const {
  return _impl.value();
}

// *** RCPP_MODULE ***
RCPP_MODULE(objective_module){
    Rcpp::class_<RcppObjective>( "Objective" )
        .method("value", &RcppObjective::value, "Get the value of the objective instance")
        ;
}
