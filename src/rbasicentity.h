#ifndef GUARD_RBasicEntity_h
#define GUARD_RBasicEntity_h

#include <string>
#include <map>
#include "ampl/entity.h"
#include "ampl/instance.h"
#include "rvar_instance.h"
#include "rcon_instance.h"
#include "robj_instance.h"
#include "rset_instance.h"
#include <Rcpp.h>

template <class T, class TW>
class RBasicEntity{
public:
  ampl::BasicEntity<T> _impl;
  RBasicEntity(ampl::BasicEntity<T>);
  std::string name() const;
  std::string toString() const;
  int indexarity() const;
  bool isScalar() const;
  int numInstances() const;
  std::vector<std::string> getIndexingSets() const;
  Rcpp::DataFrame getSuffixValues(const Rcpp::List&) const;
  Rcpp::DataFrame getValues() const;
  void setValues(const Rcpp::DataFrame&);
  SEXP get(const Rcpp::List &index) const;
  SEXP getScalar() const;
  SEXP find(const Rcpp::List &index) const;
  Rcpp::List getInstances() const;
};

RCPP_EXPOSED_CLASS_NODECL(ampl::VariantRef);

#endif
