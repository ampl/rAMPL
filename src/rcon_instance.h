#ifndef GUARD_RcppConstraintInstance_h
#define GUARD_RcppConstraintInstance_h

#include <string>
#include "ampl/entity.h"
#include "ampl/instance.h"
#include "rbasicentity.h"
#include "rcon_instance.h"
#include <Rcpp.h>

class RConstraintInstance {
public:
  ampl::ConstraintInstance _impl;
  RConstraintInstance(ampl::ConstraintInstance impl);
  std::string name() const;
  std::string toString() const;
  // bool isLogical() const;
  void drop();
  void restore();
  double body() const;
  std::string astatus() const;
  int defvar() const;
  double dinit() const;
  double dinit0() const;
  double dual() const;
  double lb() const;
  double ub() const;
  double lbs() const;
  double ubs() const;
  double ldual() const;
  double udual() const;
  double lslack() const;
  double uslack() const;
  double slack() const;
  std::string sstatus() const;
  std::string status() const;
  void setDual(double dual);
  double val() const;
};

RCPP_EXPOSED_CLASS_NODECL(RConstraintInstance)

#endif
