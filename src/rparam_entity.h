#ifndef GUARD_RcppParameter_h
#define GUARD_RcppParameter_h

#include <string>
#include "ampl/entity.h"
#include <Rcpp.h>

class RParameterEntity {
public:
  ampl::Parameter _impl;
  RParameterEntity(ampl::Parameter impl);
  bool isSymbolic() const;
  bool hasDefault() const;
  void setValues(Rcpp::DataFrame &df);
  Rcpp::DataFrame getValues() const;
  void set(SEXP value);
};

RCPP_EXPOSED_CLASS_NODECL(RParameterEntity)

#endif
