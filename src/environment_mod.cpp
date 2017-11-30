#include "environment_mod.h"
#include <Rcpp.h>

//' An AMPL environment.
//'
//' This class provides access to the environment variables and provides
//' facilities to specify where to load the underlying AMPL interpreter.
//'
//' @param binaryDirectory Optional parameter to specify the location of the AMPL binary.
//'
//' @name Environment
RcppEnvironment::RcppEnvironment()  { }
RcppEnvironment::RcppEnvironment(std::string binaryDirectory): _impl(binaryDirectory) { }

// *** RCPP_MODULE ***
RCPP_MODULE(environment_module){
    Rcpp::class_<RcppEnvironment>( "Environment" )
        .constructor("An AMPL environment")
        .constructor<std::string>("An AMPL environment")
        ;
}
