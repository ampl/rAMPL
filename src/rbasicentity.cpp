#include "rbasicentity.h"
#include "utils.h"
#include <Rcpp.h>
/*.. _secRrefEntity:
.. highlight:: r

Entity
======

*/

// Fix ld error: undefined symbol
template class RBasicEntity<ampl::VariableInstance, RVariableInstance>;
template class RBasicEntity<ampl::ObjectiveInstance, RObjectiveInstance>;
template class RBasicEntity<ampl::ConstraintInstance, RConstraintInstance>;
template class RBasicEntity<ampl::SetInstance, RSetInstance>;
template class RBasicEntity<ampl::VariantRef, ampl::VariantRef>;

/*.. class:: Entity

  Infrastructure class to enable the inheriting classes type-safe access to instances.

*/
template <class T, class TW>
RBasicEntity<T, TW>::RBasicEntity(ampl::BasicEntity<T> impl): _impl(impl) { }

/*.. method:: Entity.get(index)

  Get the instance with the specified index.
  Throws an error if an instance with the specified index does not exist,
  if it has been deleted in the underlying AMPL interpreter, or if the entity is a scalar.

  :param tuple index: The tuple specifying the index.

  :return: The corresponding instance.
*/
template <class T, class TW>
TW RBasicEntity<T, TW>::get(const Rcpp::List &index) const {
  return TW(_impl.get(list2tuple(index)));
}

template <class T, class TW>
std::string RBasicEntity<T, TW>::name() const {
  return _impl.name();
}

template <class T, class TW>
void RBasicEntity<T, TW>::setValues(const Rcpp::DataFrame &df) {
  return _impl.setValues(rdf2df(df));
}

template <class T, class TW>
Rcpp::DataFrame RBasicEntity<T, TW>::getValues() const {
  return df2rdf(_impl.getValues());
}

template <class T, class TW>
std::string RBasicEntity<T, TW>::toString() const {
  return _impl.toString();
}
