#ifndef GUARD_RObjectiveInstance_h
#define GUARD_RObjectiveInstance_h

#include <string>
#include "ampl/entity.h"
#include <Rcpp.h>

class RObjectiveInstance {
public:
  ampl::ObjectiveInstance _impl;
  RObjectiveInstance(ampl::ObjectiveInstance impl);
  double value() const;
  std::string astatus() const;
  std::string sstatus() const;
  int exitcode() const;
  std::string message() const;
  std::string result() const;
  void drop();
  void restore();
  bool minimization() const;
};

RCPP_EXPOSED_CLASS(RObjectiveInstance)

#endif
