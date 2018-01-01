#ifndef GUARD_RVariableInstance_h
#define GUARD_RVariableInstance_h

#include <string>
#include "ampl/entity.h"
#include "ampl/instance.h"
#include "rbasicinstance.h"
#include <Rcpp.h>


class RVariableInstance {
public:
  ampl::VariableInstance _impl;
  RVariableInstance(ampl::VariableInstance impl);
  std::string name() const;
  std::string toString() const;
  double value() const;
  // std::string integrality() const;
  void fix();
  void fixDbl(double value);
  void unfix();
  void setValue(double value);
  std::string astatus() const;
  int defeqn() const;
  double dual() const;
  double init() const;
  double init0() const;
  double lb() const;
  double ub() const;
  double lb0() const;
  double ub0() const;
  double lb1() const;
  double ub1() const;
  double lb2() const;
  double ub2() const;
  double lrc() const;
  double urc() const;
  double lslack() const;
  double uslack() const;
  double rc() const;
  double slack() const;
  std::string sstatus() const;
  std::string status() const;
};

RCPP_EXPOSED_CLASS(RVariableInstance)

#endif
