#ifndef GUARD_RBasicEntity_h
#define GUARD_RBasicEntity_h

#include <string>
#include "ampl/entity.h"
#include "ampl/instance.h"
#include "rvar_instance.h"
#include "rcon_instance.h"
#include "robj_instance.h"
#include <Rcpp.h>

template <class T, class TW>
class RBasicEntity{
public:
  ampl::BasicEntity<T> _impl;
  RBasicEntity(ampl::BasicEntity<T>);
  std::string name() const;
  TW get(Rcpp::List&) const;
  void setValuesDf(Rcpp::DataFrame&);
};

#endif
