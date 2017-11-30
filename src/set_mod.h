#ifndef GUARD_RcppSet_h
#define GUARD_RcppSet_h

#include <string>
#include "ampl/entity.h"
#include <Rcpp.h>

class RcppSet{
public:
  ampl::Set _impl;
  RcppSet(ampl::Set impl);
  int arity() const;
};

RCPP_EXPOSED_CLASS(RcppSet)

#endif
