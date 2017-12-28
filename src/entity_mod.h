#ifndef GUARD_RcppEntity_h
#define GUARD_RcppEntity_h

#include <string>
#include "ampl/entity.h"
#include "ampl/instance.h"
#include <Rcpp.h>

template <class T>
class RcppBasicEntity{
public:
  ampl::BasicEntity<T> _impl;
  RcppBasicEntity(ampl::BasicEntity<T>);
  T get(Rcpp::List) const;
};

typedef RcppBasicEntity<ampl::VariableInstance> RcppBEVariable;

RCPP_EXPOSED_CLASS_NODECL(RcppBEVariable)
//RCPP_EXPOSED_CLASS(RcppVariable<ampl::VariableInstance>)

#endif
