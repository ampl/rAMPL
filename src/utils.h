#ifndef GUARD_utils_h
#define GUARD_utils_h
#include <string>
#include "ampl/tuple.h"
#include "ampl/dataframe.h"
#include <Rcpp.h>

template <class T>
Rcpp::XPtr<T> getObj(const std::string &type, SEXP s) {
  std::string rtypename = "Rcpp_" + type;
  Rcpp::S4 s4obj(s);
  if ( !s4obj.is( rtypename.c_str() ) ) {
    Rf_error( (std::string("object is not of the type ")+type).c_str() );
  }
  Rcpp::Environment env(s4obj);
  Rcpp::XPtr<T> xptr(env.get(".pointer"));
  return xptr;
}

ampl::Tuple list2tuple(Rcpp::List list);
Rcpp::List tuple2list(const ampl::Tuple &tuple);

ampl::DataFrame rdf2df(Rcpp::DataFrame rdf, int numberOfIndexColumns = -1);

Rcpp::DataFrame df2rdf(const ampl::DataFrame &df);

SEXP variant2sexp(const ampl::Variant &value);

#endif
