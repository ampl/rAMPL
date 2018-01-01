#include "rbasicinstance.h"
#include "utils.h"
#include <Rcpp.h>

template class RBasicInstance<ampl::VariableInstance>;

template <class T>
RBasicInstance<T>::RBasicInstance(T impl): __impl(impl) { }


template <class T>
std::string RBasicInstance<T>::name() const {
  printf(">>>>>name()!!!<<<<<<\n");
  return __impl.name();
}
