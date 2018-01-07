#include "utils.h"
#include <Rcpp.h>



ampl::Tuple list2tuple(const Rcpp::List &list) {
  int p = 0;
  ampl::Variant arguments[list.size()];
  for(Rcpp::List::const_iterator it = list.begin(); it != list.end(); it++) {
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
  return ampl::Tuple(arguments, list.size());
}

Rcpp::List tuple2list(const ampl::TupleRef &tuple) {
  Rcpp::List list(tuple.size());
  for(int i = 0; i < tuple.size(); i++) {
    const ampl::VariantRef &e = tuple[i];
    if(e.type() == ampl::NUMERIC) {
      list[i] = e.dbl();
    } else {
      list[i] = e.str();
    }
  }
  return list;
}

ampl::DataFrame rdf2df(const Rcpp::DataFrame &rdf){
  int nrows = rdf.nrows();
  int ncols = rdf.length();
  const char *names[ncols];
  Rcpp::CharacterVector colnames = rdf.names();
  for(int i = 0; i < colnames.size(); i++){
    names[i] = Rcpp::as<const char *>(colnames[i]);
  }
  ampl::DataFrame df(ncols-1, ampl::StringArgs(names, ncols));
  int p = 0;
  for(Rcpp::DataFrame::const_iterator it = rdf.begin(); it != rdf.end(); it++){
    switch(TYPEOF(*it)) {
      case REALSXP:
        df.setColumn(names[p++], Rcpp::as<std::vector<double> >(*it).data(), nrows);
        break;
      case INTSXP:
        if(::Rf_isFactor(*it) == false) {
          Rcpp::IntegerVector iv = *it;
          std::vector<double> dbl_column(iv.size());
          for(int i = 0; i < iv.size(); i++) {
            dbl_column[i] = iv[i];
          }
          df.setColumn(names[p++], dbl_column.data(), dbl_column.size());
        } else{
          Rcpp::IntegerVector iv = *it;
          std::vector<const char *> str_column(iv.size());
          std::vector<std::string > levels = Rcpp::as<std::vector<std::string> >(iv.attr("levels"));
          for(int i = 0; i < iv.size(); i++) {
            str_column[i] = levels[iv[i]-1].c_str();
          }
          df.setColumn(names[p++], str_column.data(), str_column.size());
        }
        break;
      default:
        Rcpp::stop("invalid type");
    }
  }
  return df;
}

Rcpp::DataFrame df2rdf(const ampl::DataFrame &df){
  Rcpp::List tmp;
  int nrows = df.getNumRows();
  int ncols = df.getNumCols();
  ampl::StringRefArray headers = df.getHeaders();
  for(int i = 0; i < ncols; i++){
    ampl::DataFrame::Column col = df.getColumn(headers[i]);
    bool numeric = true;
    for(ampl::DataFrame::Column::iterator it = col.begin(); it != col.end(); it++){
      if(it->type() != ampl::NUMERIC) {
        numeric = false;
        break;
      }
    }
    if(numeric) {
      std::vector<double> dbl_column;
      for(ampl::DataFrame::Column::iterator it = col.begin(); it != col.end(); it++){
        dbl_column.push_back(it->dbl());
      }
      tmp[headers[i]] = dbl_column;
    } else {
      std::vector<std::string> str_column;
      for(ampl::DataFrame::Column::iterator it = col.begin(); it != col.end(); it++){
        str_column.push_back(it->str());
      }
      tmp[headers[i]] = str_column;
    }
  }
  return Rcpp::DataFrame(tmp);
}
