#ifndef GUARD_RcppParameter_h
#define GUARD_RcppParameter_h

#include <string>
#include "ampl/entity.h"
#include "rbasicentity.h"
#include <Rcpp.h>

class RParameterEntity: public RBasicEntity<ampl::Variant, ampl::Variant>{
public:
  ampl::Parameter _impl;
  RParameterEntity(ampl::Parameter impl);
  bool isSymbolic() const;
  bool hasDefault() const;
  void setValues(Rcpp::DataFrame df);
  Rcpp::DataFrame getValues() const;
  SEXP value() const;
  void set(SEXP value);
  void setIndVal(Rcpp::List index, SEXP value);
  SEXP get(Rcpp::List index) const;
  SEXP getScalar() const;
  SEXP find(Rcpp::List index) const;
  Rcpp::List getInstances() const;
};

RCPP_EXPOSED_CLASS_NODECL(RParameterEntity)

#endif
