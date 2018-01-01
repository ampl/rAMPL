#ifndef GUARD_RBasicInstance_h
#define GUARD_RBasicInstance_h

#include <string>
#include "ampl/entity.h"
#include "ampl/instance.h"
#include "rbasicinstance.h"
#include <Rcpp.h>

template <class T>
class RBasicInstance{
public:
  T __impl;
  RBasicInstance(T);
  std::string name() const;
};

#endif
