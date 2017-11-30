#ifndef GUARD_RcppParameter_h
#define GUARD_RcppParameter_h

#include <string>
#include "ampl/entity.h"
#include <Rcpp.h>

class RcppParameter{
public:
  ampl::Parameter _impl;
  RcppParameter(ampl::Parameter impl);
  bool isSymbolic() const;
};

RCPP_EXPOSED_CLASS(RcppParameter)

#endif
