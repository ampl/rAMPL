#ifndef GUARD_RcppConstraint_h
#define GUARD_RcppConstraint_h

#include <string>
#include "ampl/entity.h"
#include <Rcpp.h>

class RcppConstraint{
public:
  ampl::Constraint _impl;
  RcppConstraint(ampl::Constraint impl);
  bool isLogical() const;
};

RCPP_EXPOSED_CLASS(RcppConstraint)

#endif
