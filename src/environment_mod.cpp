#include "environment_mod.h"
#include <Rcpp.h>

RcppEnvironment::RcppEnvironment()  { }
RcppEnvironment::RcppEnvironment(std::string binaryDirectory): _impl(binaryDirectory) { }

// *** RCPP_MODULE ***
RCPP_MODULE(environment_module){
    Rcpp::class_<RcppEnvironment>( "Environment" )
        .constructor("An AMPL environment")
        .constructor<std::string>("An AMPL environment")
        ;
}
