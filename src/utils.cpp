#include "utils.h"
#include <Rcpp.h>



ampl::Tuple list2tuple(Rcpp::List index) {
  int p = 0;
  ampl::Variant arguments[index.size()];
  for(Rcpp::List::iterator it = index.begin(); it != index.end(); it++) {
    switch(TYPEOF(*it)) {
      case REALSXP:
        arguments[p++] = ampl::Variant(Rcpp::as<double>(*it));
        break;
      case INTSXP:
        arguments[p++] = ampl::Variant(Rcpp::as<int>(*it));
        break;
      case STRSXP:
        arguments[p++] = ampl::Variant(Rcpp::as<std::string>(*it));
        break;
	    default:
        Rcpp::stop("only accepts lists containing numbers and strings");
    }
  }
  return ampl::Tuple(arguments, index.size());
}
