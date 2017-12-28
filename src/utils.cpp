#include "utils.h"
#include <Rcpp.h>



ampl::Tuple list2tuple(Rcpp::List index) {
  int p = 0;
  ampl::Tuple tuple(index.size());
  for(Rcpp::List::iterator it = index.begin(); it != index.end(); it++) {
    switch(TYPEOF(*it)) {
      case REALSXP:
        tuple[p++] = ampl::Variant(Rcpp::as<double>(*it));
        break;
      case INTSXP:
        tuple[p++] = ampl::Variant(Rcpp::as<int>(*it));
        break;
      case STRSXP:
        tuple[p++] = ampl::Variant(Rcpp::as<std::string>(*it));
        break;
	    default:
        Rcpp::stop("only accepts lists containing numbers and strings");
    }
  }
  return tuple;
}
