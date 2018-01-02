#ifndef GUARD_RObjectiveEntity_h
#define GUARD_RObjectiveEntity_h

#include <string>
#include "ampl/entity.h"
#include "ampl/instance.h"
#include "rbasicentity.h"
#include "robj_instance.h"
#include <Rcpp.h>

class RObjectiveEntity: public RBasicEntity<ampl::ObjectiveInstance, RObjectiveInstance>{
public:
  ampl::Objective _impl;
  RObjectiveEntity(ampl::Objective impl);
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

RCPP_EXPOSED_CLASS(RObjectiveEntity)

#endif
