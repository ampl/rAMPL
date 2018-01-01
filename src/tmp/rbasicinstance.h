#ifndef GUARD_RcppEntity_h
#define GUARD_RcppEntity_h

#include <string>
#include "ampl/entity.h"
#include "ampl/instance.h"
#include <Rcpp.h>

template <class T>
class RBasicInstance{
public:
  ampl::BasicInstance<T> _impl;
  RBasicInstance(ampl::BasicInstance<T>);
};

//typedef RBasicInstance<ampl::VariableInstance> RVariableInstance;

//RCPP_EXPOSED_CLASS_NODECL(RVariableInstance)

#endif
