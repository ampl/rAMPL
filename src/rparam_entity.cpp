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


/*.. method:: Parameter.setValues(values)

  If the argument is a `list`,
  assign the specified values to this parameter, assigning them to
  the parameter in the same order as the indices in the entity.
  The number of values in the array must be equal to the
  specified size.

  If the argument is a `data.frame`,
  set the values of this parameter to the correponding values of the `data.frame`
  indexed over the same sets (or a subset). All columns but the last are used as index, and the last is used as value.

  :param list/data.frame values: An array of indices of the instances to be set.
*/
void RParameterEntity::setValues(Rcpp::DataFrame& df) {
  if(df.length() == 1){
    switch(TYPEOF(df[0])) {
      case REALSXP:
        _impl.setValues(Rcpp::as<std::vector<double> >(df[0]).data(), df.nrows());
        break;
      case INTSXP:
        if(::Rf_isFactor(df[0]) == false) {
          _impl.setValues(Rcpp::as<std::vector<double> >(df[0]).data(), df.nrows());
        } else {
          Rcpp::IntegerVector iv = df[0];
          std::vector<const char *> values(iv.size());
          std::vector<std::string > levels = Rcpp::as<std::vector<std::string> >(iv.attr("levels"));
          for(int i = 0; i < iv.size(); i++) values[i] = levels[iv[i]-1].c_str();
          _impl.setValues(values.data(), values.size());
        }
        break;
	    default:
        Rcpp::stop("invalid type");
    }
  } else {
    _impl.setValues(rdf2df(df));
  }
}

Rcpp::DataFrame RParameterEntity::getValues() const {
  return df2rdf(_impl.getValues());
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
    .method("setValues", &RParameterEntity::setValues, "Assign the specified values to this parameter")
    .method("getValues", &RParameterEntity::getValues, "Get the values of this parameter")
    .method("set", &RParameterEntity::set, "Set the value of a scalar parameter")
    ;
}
