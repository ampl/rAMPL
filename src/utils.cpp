#include "utils.h"
#include <Rcpp.h>

ampl::Tuple list2tuple(Rcpp::List list) {
  int p = 0;
  ampl::Variant arguments[list.size()];
  for(Rcpp::List::iterator it = list.begin(); it != list.end(); it++) {
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

Rcpp::List tuple2list(const ampl::Tuple &tuple) {
  Rcpp::List list(tuple.size());
  for(std::size_t i = 0; i < tuple.size(); i++) {
    const ampl::Variant &e = tuple[i];
    if(e.type() == ampl::NUMERIC) {
      list[i] = e.dbl();
    } else {
      list[i] = e.str();
    }
  }
  return list;
}

ampl::DataFrame rdf2df(Rcpp::DataFrame rdf, int numberOfIndexColumns){
  int nrows = rdf.nrows();
  int ncols = rdf.length();
  const char *names[ncols];
  Rcpp::CharacterVector colnames = rdf.names();
  for(int i = 0; i < colnames.size(); i++){
    names[i] = Rcpp::as<const char *>(colnames[i]);
  }
  if(numberOfIndexColumns == -1){
    numberOfIndexColumns = ncols - 1;
  }
  ampl::DataFrame df(numberOfIndexColumns, ampl::StringArgs(names, ncols));
  int p = 0;
  for(Rcpp::DataFrame::iterator it = rdf.begin(); it != rdf.end(); it++){
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
      case STRSXP: {
          Rcpp::StringVector iv = *it;
          std::vector<const char *> str_column(iv.size());
          for(int i = 0; i < iv.size(); i++) {
            str_column[i] = iv[i];
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
  int ncols = df.getNumCols();
  ampl::StringArray headers = df.getHeaders();
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

SEXP variant2sexp(const ampl::Variant &value) {
  if(value.type() == ampl::NUMERIC) {
    return Rcpp::wrap(value.dbl());
  } else if(value.type() == ampl::STRING) {
    return Rcpp::wrap(value.str());
  } else {
    return Rcpp::wrap(Rcpp::String(NA_STRING));
  }
}
