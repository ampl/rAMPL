#include "rbasicinstance.h"
#include "utils.h"
#include <Rcpp.h>
/*.. _secRrefEntity:
.. highlight:: r

Entity
======

*/

// Fix ld error: undefined symbol
template class RBasicInstance<ampl::VariableInstance>;

/*.. class:: Entity

  Infrastructure class to enable the inheriting classes type-safe access to instances.

*/
template <class T>
RBasicInstance<T>::RBasicInstance(ampl::BasicInstance<T> impl): _impl(impl) { }

// *** RCPP_MODULE ***
/*RCPP_MODULE(entity_module){
    Rcpp::class_<RBasicInstance>( "Entity" )
        .method("get", &RBasicInstance::get, "Get the instance with the specified index")
        .const_method( "[[", &RBasicInstance::get)
        ;
}*/
