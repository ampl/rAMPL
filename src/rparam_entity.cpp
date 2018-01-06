#include "rparam_entity.h"
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
RParameterEntity::RParameterEntity(ampl::Parameter impl): _impl(impl) { }

/*.. method:: Parameter.isSymbolic()

  Returns true if the parameter is declared as symbolic (can store both numerical and string values).

  :return: ``TRUE`` if the parameter is declared as symbolic.
*/
bool RParameterEntity::isSymbolic() const {
  return _impl.isSymbolic();
}

/*.. method:: Parameter.hasDefault()

  Check if the parameter has a default initial value. In case of the following AMPL code::

    param a;
    param b default a;

  the function will return ``TRUE`` for parameter ``b``.

  :return: ``TRUE`` if the parameter has a default initial value. Please note
           that if the parameter has a default expression which refers to
           another parameter which value is not defined, this will return true.
*/
bool RParameterEntity::hasDefault() const {
  return _impl.hasDefault();
}

/*.. method:: Parameter.setValues(indices, values)

  Assign the values (string or numeric) to the parameter instances with the
  specified indices, equivalent to the AMPL code::

    let {i in indices} par[i] := values[i];


  :param list indices: An array of indices of the instances to be set.
  :param list values: Values to set.
*/
void RParameterEntity::setValuesIndVal(Rcpp::List indices, Rcpp::List values) {
  //ampl::Tuple _indices[indices.size()];
  //ampl::Variant _values[indices.size()];
  //return _impl.setValues(_indices, _values, indices.size());
}

void RParameterEntity::setValuesDf(Rcpp::DataFrame& df) {
  if(df.length() == 1){
    Rcpp::List  values = df[0];
    this->setValuesList(values);
  } else {
    _impl.setValues(rdf2df(df));
  }
}

/*.. method:: Parameter.setValues(values)

  Assign the specified values to this parameter, assigning them to
  the parameter in the same order as the indices in the entity.
  The number of values in the array must be equal to the
  specified size.

  :param list values: An array of indices of the instances to be set.
  :param values indices: Values to be assigned.
*/
void RParameterEntity::setValuesList(Rcpp::List &values) {
  bool numeric = true;
  for(Rcpp::List::iterator it = values.begin(); it != values.end(); it++) {
    if(TYPEOF(*it) == STRSXP) {
      numeric = false;
      break;
    }
  }
  if(numeric) {
    int p = 0;
    double _values[values.size()];
    for(Rcpp::List::iterator it = values.begin(); it != values.end(); it++) {
      switch(TYPEOF(*it)) {
        case REALSXP:
          _values[p++] = Rcpp::as<double>(*it);
          break;
        case INTSXP:
          _values[p++] = Rcpp::as<int>(*it);
          break;
  	    default:
          Rcpp::stop("all values must be of the same type (numeric/strings)");
      }
    }
    _impl.setValues(_values, values.size());
  } else {
    int p = 0;
    std::string _tmp[values.size()];
    const char *_values[values.size()];
    for(Rcpp::List::iterator it = values.begin(); it != values.end(); it++) {
      switch(TYPEOF(*it)) {
        case STRSXP:
          _tmp[p] = Rcpp::as<std::string>(*it);
          _values[p] = _tmp[p].c_str();
          p++;
          break;
        default:
          Rcpp::stop("all values must be of the same type (numeric/strings)");
      }
    }
    _impl.setValues(_values, values.size());
  }
}

/*.. method:: Parameter.set(value)

  Set the value of a scalar parameter.

  :param value: Value to be assigned.
*/
void RParameterEntity::set(SEXP value) {
  switch(TYPEOF(value)) {
    case REALSXP:
      _impl.set(Rcpp::as<double>(value));
      break;
    case INTSXP:
      _impl.set(Rcpp::as<int>(value));
      break;
    case STRSXP:
      _impl.set(Rcpp::as<std::string>(value));
      break;
    default:
      Rcpp::stop("the value must be number or string");
  }
}

// *** RCPP_MODULE ***
RCPP_MODULE(rparam_entity){
  Rcpp::class_<RParameterEntity>( "Parameter" )
    .method("isSymbolic", &RParameterEntity::isSymbolic, "Returns true if the parameter is declared as symbolic")
    .method("setValues", &RParameterEntity::setValuesDf, "Assign the specified values to this parameter")
    .method("set", &RParameterEntity::set, "Set the value of a scalar parameter")
    ;
}
