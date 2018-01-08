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
  Rcpp::String get(std::string name) const;
  void put(std::string name, std::string value);
  void setBinDir(std::string binaryDirectory);
  std::string getBinDir() const;
  std::string toString() const;
  Rcpp::List list() const;
};

RCPP_EXPOSED_CLASS(REnvironment)

#endif
