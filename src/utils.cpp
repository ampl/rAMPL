#include "utils.h"
#include <Rcpp.h>



ampl::Tuple list2tuple(Rcpp::List &index) {
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

ampl::DataFrame rdf2df(Rcpp::DataFrame &rdf){
  int nrows = rdf.nrows();
  int ncols = rdf.length();
  Rcpp::CharacterVector colnames = rdf.names();
  int p = 0;
  const char *names[ncols];
  for(Rcpp::CharacterVector::iterator it = colnames.begin(); it != colnames.end(); it++){
    names[p++] = Rcpp::as<const char *>(*it);
    printf(">>%s<<\n", names[p-1]);
  }
  ampl::DataFrame df(ncols-1, ampl::StringArgs(names, ncols));
  p = 0;
  const char *str_column[nrows];
  for(Rcpp::DataFrame::iterator it = rdf.begin(); it != rdf.end(); it++){
    switch(TYPEOF(*it)) {
      case REALSXP:
        {
          printf("$$real$$\n");
          df.setColumn(names[p++], Rcpp::as<std::vector<double> >(*it).data(), nrows);
        }
        break;
      case INTSXP:
        if(::Rf_isFactor(*it) == false) {
          printf("$$integer$$\n");
          df.setColumn(names[p++], Rcpp::as<std::vector<double> >(*it).data(), nrows);
        } else{
          printf("$$factor$$\n");
          Rcpp::IntegerVector iv = *it;
          std::vector<std::string > levels = Rcpp::as<std::vector<std::string> >(iv.attr("levels"));
          for(int i = 0; i < levels.size(); i++) printf(">>>%s\n", levels[i].c_str());
          for(int i = 0; i < iv.size(); i++) str_column[i] = levels[iv[i]-1].c_str();
          df.setColumn(names[p++], str_column, nrows);
        }
        break;
      case STRSXP:
        {
          printf("$$string$$\n");
          std::vector<std::string> vs = Rcpp::as<std::vector<std::string> >(*it);
          for(int i = 0; i < vs.size(); i++) str_column[i] = vs[i].c_str();
          df.setColumn(names[p++], str_column, nrows);
        }
        break;
      default:
        Rcpp::stop("only accepts lists containing numbers and strings");
    }
  }
  return df;
}
