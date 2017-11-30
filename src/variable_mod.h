#ifndef GUARD_RcppVariable_h
#define GUARD_RcppVariable_h

#include <string>
#include "ampl/entity.h"
#include <Rcpp.h>

class RcppVariable{
public:
  ampl::Variable _impl;
  RcppVariable(ampl::Variable impl);
  double value() const;
};

RCPP_EXPOSED_CLASS(RcppVariable)

#endif
