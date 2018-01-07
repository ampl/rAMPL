#ifndef GUARD_REnvironment_h
#define GUARD_REnvironment_h

#include <string>
#include "ampl/ampl.h"
#include <Rcpp.h>

class REnvironment{
public:
  ampl::Environment _impl;
  REnvironment();
  REnvironment(std::string binaryDirectory);
};

#endif
