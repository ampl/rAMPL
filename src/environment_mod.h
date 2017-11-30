#ifndef GUARD_RcppEnvironment_h
#define GUARD_RcppEnvironment_h

#include <string>
#include "ampl/ampl.h"
#include <Rcpp.h>

class RcppEnvironment{
public:
  ampl::Environment _impl;
  RcppEnvironment();
  RcppEnvironment(std::string binaryDirectory);
};

#endif
