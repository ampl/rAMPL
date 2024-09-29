#include "rparam_entity.h"
#include "utils.h"
#include <Rcpp.h>
/*.. _secRrefParamEntity:
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
RParameterEntity::RParameterEntity(ampl::Parameter impl): RBasicEntity<ampl::Variant, ampl::Variant>(impl), _impl(impl) { }

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
void RParameterEntity::setValues(Rcpp::DataFrame df) {
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
      case STRSXP: {
          Rcpp::StringVector iv = df[0];
          std::vector<const char *> values(iv.size());
          for(int i = 0; i < iv.size(); i++) {
            values[i] = iv[i];
          }
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

/*.. method:: Parameter.value()

  Get the value of a scalar parameter.
*/
SEXP RParameterEntity::value() const {
  ampl::Variant value = _impl.get();
  if(value.type() == ampl::NUMERIC) {
    return Rcpp::wrap(value.dbl());
  } else {
    return Rcpp::wrap(value.str());
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

/*.. method:: Parameter.set(index, value)

  Set the value of a single instance of this parameter.

  :param list index: index of the instance to be set.
  :param value: Value to be assigned.
*/
void RParameterEntity::setIndVal(Rcpp::List index, SEXP value) {
  switch(TYPEOF(value)) {
    case REALSXP:
      _impl.set(list2tuple(index), Rcpp::as<double>(value));
      break;
    case STRSXP:
      _impl.set(list2tuple(index), Rcpp::as<std::string>(value));
      break;
    default:
      Rcpp::stop("the value must be numeric or string");
  }
}

// RBasicEntity<ampl::Variant, ampl::Variant>
SEXP RParameterEntity::get(Rcpp::List index) const {
  return variant2sexp(_impl.get(list2tuple(index)));
}

SEXP RParameterEntity::getScalar() const {
  return variant2sexp(_impl.get());
}

SEXP RParameterEntity::find(Rcpp::List index) const {
  std::map<ampl::Tuple, ampl::Variant> instances = _impl.getInstances();
  typename std::map<ampl::Tuple, ampl::Variant>::iterator it = instances.find(list2tuple(index));
  if(it != instances.end()) {
    return variant2sexp(it->second);
  } else {
    return R_NilValue;
  }
}

Rcpp::List RParameterEntity::getInstances() const {
  Rcpp::List list;
  std::map<ampl::Tuple, ampl::Variant> instances = _impl.getInstances();
  for(typename std::map<ampl::Tuple, ampl::Variant>::iterator it = instances.begin(); it != instances.end(); it++) {
    Rcpp::List row = tuple2list(it->first);
    row.push_back(variant2sexp(it->second));
    list.push_back(row);
  }
  return list;
}

// *** RCPP_MODULE ***
RCPP_MODULE(rparam_entity){
  Rcpp::class_<RBasicEntity<ampl::Variant, ampl::Variant> >("PEntity")
    .const_method("name", &RBasicEntity<ampl::Variant, ampl::Variant>::name)
    .const_method("toString", &RBasicEntity<ampl::Variant, ampl::Variant>::toString)
    .const_method("indexarity", &RBasicEntity<ampl::Variant, ampl::Variant>::indexarity)
    .const_method("isScalar", &RBasicEntity<ampl::Variant, ampl::Variant>::isScalar)
    .const_method("numInstances", &RBasicEntity<ampl::Variant, ampl::Variant>::numInstances)
    .const_method("getIndexingSets", &RBasicEntity<ampl::Variant, ampl::Variant>::getIndexingSets)
    .const_method("xref", &RBasicEntity<ampl::Variant, ampl::Variant>::xref)
    //.const_method("getValues", &RBasicEntity<ampl::VariantRef, ampl::VariantRef>::getSuffixValues)
    //.const_method("getValues", &RBasicEntity<ampl::VariantRef, ampl::VariantRef>::getValues)
    //.method("setValues", &RBasicEntity<ampl::VariantRef, ampl::VariantRef>::setValues)
    //.const_method("[[", &RBasicEntity<ampl::Variant, ampl::Variant>::get)
    //.const_method("get", &RBasicEntity<ampl::Variant, ampl::Variant>::get)
    //.const_method("get", &RBasicEntity<ampl::Variant, ampl::Variant>::getScalar)
    //.const_method("find", &RBasicEntity<ampl::Variant, ampl::Variant>::find)
    //.const_method("getInstances", &RBasicEntity<ampl::Variant, ampl::Variant>::getInstances)
    ;
  Rcpp::class_<RParameterEntity>("Parameter")
    .derives<RBasicEntity<ampl::Variant, ampl::Variant> >("PEntity")
    .method("[[<-", &RParameterEntity::setIndVal)
    .method("isSymbolic", &RParameterEntity::isSymbolic, "Returns true if the parameter is declared as symbolic")
    .method("setValues", &RParameterEntity::setValues, "Assign the specified values to this parameter")
    .method("getValues", &RParameterEntity::getValues, "Get the values of this parameter")
    .method("value", &RParameterEntity::value, "Get the value of a scalar parameter")
    .method("set", &RParameterEntity::setIndVal, "Set the value of an indexed parameter")
    .method("set", &RParameterEntity::set, "Set the value of a scalar parameter")
    .const_method("[[", &RParameterEntity::get)
    .const_method("get", &RParameterEntity::get)
    .const_method("get", &RParameterEntity::getScalar)
    .const_method("find", &RParameterEntity::find)
    .const_method("getInstances", &RParameterEntity::getInstances)
    ;
}