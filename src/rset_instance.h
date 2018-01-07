#ifndef GUARD_RSetInstance_h
#define GUARD_RSetInstance_h

#include <string>
#include "ampl/entity.h"
#include <Rcpp.h>

class RSetInstance {
public:
  ampl::SetInstance _impl;
  RSetInstance(ampl::SetInstance impl);
  //int arity() const; FIXME: ?
  int size() const;
  std::vector<Rcpp::List> members() const;
  bool contains(Rcpp::List tuple) const;
  Rcpp::DataFrame getValues() const;
  void setValues(SEXP values);
  void setValuesList(const Rcpp::List &values);
};

RCPP_EXPOSED_CLASS(RSetInstance)

#endif
