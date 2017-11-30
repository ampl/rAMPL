#ifndef GUARD_RcppObjective_h
#define GUARD_RcppObjective_h

#include <string>
#include "ampl/entity.h"
#include <Rcpp.h>

class RcppObjective{
public:
  ampl::Objective _impl;
  RcppObjective(ampl::Objective impl);
  double value() const;
};

RCPP_EXPOSED_CLASS(RcppObjective)

#endif
