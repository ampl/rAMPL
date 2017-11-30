#include "parameter_mod.h"
#include "utils.h"
#include <Rcpp.h>
/*.. _secRrefAMPL:
.. highlight:: r

Parameter
=========

*/

/*.. class:: Parameter

  Represents an AMPL parameter. The values can be float or string (in case of
  symbolic parameters).

  Data can be assigned to the set using the methods
  :meth:`~Parameter.set` and :meth:`~Parameter.setValues` or
  using :meth:`~AMPL.setData` and an object of class
  :class:`~DataFrame`.
*/
RcppParameter::RcppParameter(ampl::Parameter impl): _impl(impl) { }

/*.. method:: Parameter.isSymbolic()

  Returns true if the parameter is declared as symbolic (can store both numerical and string values).

  :return: ``TRUE`` if the parameter is declared as symbolic.
*/
bool RcppParameter::isSymbolic() const {
  return _impl.isSymbolic();
}

// *** RCPP_MODULE ***
RCPP_MODULE(parameter_module){
    Rcpp::class_<RcppParameter>( "Parameter" )
        .method("isSymbolic", &RcppParameter::isSymbolic, "Returns true if the parameter is declared as symbolic")
        ;
}
