#ifndef GUARD_RSetEntity_h
#define GUARD_RSetEntity_h

#include <string>
#include <vector>
#include "ampl/entity.h"
#include "ampl/instance.h"
#include "rbasicentity.h"
#include "rset_instance.h"
#include <Rcpp.h>

class RSetEntity: public RBasicEntity<ampl::SetInstance, RSetInstance> {
public:
  ampl::Set _impl;
  RSetEntity(ampl::Set impl);
  int arity() const;
  int size();// const;
  std::vector<Rcpp::List> members();// const;
  bool contains(Rcpp::List tuple) const;
  Rcpp::DataFrame getValues() const;
  void setValues(SEXP values);
  void setValuesList(Rcpp::List values);
};

RCPP_EXPOSED_CLASS(RSetEntity)

#endif
