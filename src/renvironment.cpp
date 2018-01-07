#include "renvironment.h"
#include <Rcpp.h>
/*.. _secRrefEnv:
.. highlight:: r

Environment
===========

*/

/*.. class:: Environment


*/
REnvironment::REnvironment()  { }
REnvironment::REnvironment(std::string binaryDirectory): _impl(binaryDirectory) { }

// *** RCPP_MODULE ***
RCPP_MODULE(renvironment){
  Rcpp::class_<REnvironment>( "Environment" )
    .constructor("An AMPL environment")
    .constructor<std::string>("An AMPL environment")
    ;
}
