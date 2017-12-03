#ifndef GUARD_RcppVariable_h
#define GUARD_RcppVariable_h

#include <string>
#include "ampl/entity.h"
#include "ampl/instance.h"
#include <Rcpp.h>

template <class T>
class RcppVariable{
public:
  T _impl;
  RcppVariable(T impl);
  double value() const;
  std::string integrality() const;
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
  //RcppVariable<ampl::VariableInstance> get(Rcpp::List) const;
};

typedef RcppVariable<ampl::Variable> RcppVariableEntity;

RCPP_EXPOSED_CLASS_NODECL(RcppVariableEntity)
//RCPP_EXPOSED_CLASS(RcppVariable<ampl::VariableInstance>)

#endif
