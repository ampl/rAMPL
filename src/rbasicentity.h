#ifndef GUARD_RBasicEntity_h
#define GUARD_RBasicEntity_h

#include <string>
#include <map>
#include "ampl/ampl.h"
#include "ampl/entity.h"
#include "utils.h"
#include <Rcpp.h>
/*.. _secRrefEntity:
.. highlight:: r

Entity
======

*/


template <class T, class TW>
class RBasicEntity{
public:
  ampl::BasicEntity<T> _impl;
  RBasicEntity(ampl::BasicEntity<T>);
  std::string name() const;
  std::string toString() const;
  int indexarity() const;
  bool isScalar() const;
  int numInstances() const;
  std::vector<std::string> getIndexingSets() const;
  std::vector<std::string> xref() const;
  Rcpp::DataFrame getSuffixValues(const Rcpp::List) const;
  Rcpp::DataFrame getValues() const;
  void setValues(Rcpp::DataFrame);
  SEXP get(Rcpp::List index) const;
  SEXP getScalar() const;
  SEXP find(Rcpp::List index) const;
  Rcpp::List getInstances() const;
};

RCPP_EXPOSED_CLASS_NODECL(ampl::Variant);

/*.. class:: Entity

  Infrastructure class to enable the inheriting classes type-safe access to instances.

*/
template <class T, class TW>
RBasicEntity<T, TW>::RBasicEntity(ampl::BasicEntity<T> impl): _impl(impl) { }

/*.. method:: Entity.name()

  Get the name of this entity.

  :return: The name of this entity.
*/
template <class T, class TW>
std::string RBasicEntity<T, TW>::name() const {
  return _impl.name();
}


/*.. method:: Entity.toString()

   Returns a string representation of this entity (its declaration).

  :return: The string representation of this entity.
*/
template <class T, class TW>
std::string RBasicEntity<T, TW>::toString() const {
  return _impl.toString();
}

/*.. method:: Entity.indexarity()

  Get the indexarity of this entity (sum of the dimensions of the indexing
  sets).
  This value indicates the arity of the Tuple to be passed to the method
  :meth:`~.Entity.get` in order to access an instance of this entity.
  See the following AMPL examples::

    var x;               # indexarity = 0
    var y {1..2};        # indexarity = 1
    var z {1..2,3..4};   # indexarity = 2
    var zz {{(1, 2)}};   # indexarity = 2

  :return: The sum of the dimensions of the indexing sets or 0 if the entity is not indexed.
*/
template <class T, class TW>
int RBasicEntity<T, TW>::indexarity() const {
  return _impl.indexarity();
}

/*.. method:: Entity.isScalar()

  Check whether this entity is scalar. Equivalent to testing whether
  indexarity is equal to zero.

  :return: ``TRUE`` if the entity is scalar (not indexed over any set).
*/
template <class T, class TW>
bool RBasicEntity<T, TW>::isScalar() const {
  return _impl.isScalar();
}

/*.. method:: Entity.numInstances()

  Get the number of instances in this entity.

  :return: The number of instances in this entity.
*/
template <class T, class TW>
int RBasicEntity<T, TW>::numInstances() const {
  return _impl.numInstances();
}

/*.. method:: Entity.getIndexingSets()

  Get a list with the AMPL string representation of the sets on which this entity is
  indexed.

  :return: The string representation of the indexing sets for this entity or an empty list if the entity is scalar.
*/
template <class T, class TW>
std::vector<std::string> RBasicEntity<T, TW>::getIndexingSets() const {
  ampl::StringArray sa = _impl.getIndexingSets();
  return std::vector<std::string>(sa.begin(), sa.end());
}

/*.. method:: Entity.xref()

  Get the names of all entities which depend on this one.

  :return: A list with the names of all entities which depend on this one.
*/
template <class T, class TW>
std::vector<std::string> RBasicEntity<T, TW>::xref() const {
  ampl::StringArray sa = _impl.xref();
  return std::vector<std::string>(sa.begin(), sa.end());
}

/*.. method:: Entity.getValues()

  Get the principal values of this entity as a `data.frame`. The specific returned
  value depends on the type of entity (see list below).

  For:
  * Variables and Objectives it returns the suffix ``val``
  * Parameters it returns their values
  * Constraints it returns the suffix ``dual``
  * Sets it returns all the members of the set. Note that it does not
  * apply to indexed sets. See :meth:`~.SetInstance.getValues`

  :return: A `data.frame` containing the values for all instances.
*/
template <class T, class TW>
Rcpp::DataFrame RBasicEntity<T, TW>::getValues() const {
  return df2rdf(_impl.getValues());
}

/*.. method:: Entity.getValues(suffixes)

  Get the specified suffixes value for all instances in a `data.frame`.

  :param list suffixes: Suffixes to get.

  :return: A `data.frame` containing the specified values.
*/
template <class T, class TW>
Rcpp::DataFrame RBasicEntity<T, TW>::getSuffixValues(Rcpp::List suffixes) const {
  std::vector<const char *> tmp(suffixes.size());
  for(int i = 0; i < suffixes.size(); i++) {
    tmp[i] = Rcpp::as<const char *>(suffixes[i]);
  }
  return df2rdf(_impl.getValues(ampl::StringArgs(tmp.data(), tmp.size())));
}

/*.. method:: Entity.setValues(data)

  Set the values of this entiy to the correponding values of a
  DataFrame indexed over the same sets (or a subset).
  This function assigns the values in the first data column of
  the passed dataframe to the entity the function is called from.
  In particular, the statement::

    x.setValues(y.getValues())

  is semantically equivalent to the AMPL statement::

    let {s in S} x[s] := y[s];

  :param `data.frame` data: The data to set the entity to.
*/
template <class T, class TW>
void RBasicEntity<T, TW>::setValues(Rcpp::DataFrame data) {
  _impl.setValues(rdf2df(data));
}

/*.. method:: Entity.get(index)

  Get the instance with the specified index.
  Throws an error if an instance with the specified index does not exist,
  if it has been deleted in the underlying AMPL interpreter, or if the index does not match the indexarity.
  Also works for scalar entities with an empty list as argument.

  :param tuple index: The list specifying the index.

  :return: The corresponding instance.
*/
template <class T, class TW>
SEXP RBasicEntity<T, TW>::get(Rcpp::List index) const {
  if(index.size() == 0) {
    return Rcpp::wrap(TW(_impl.get()));
  } else {
    return Rcpp::wrap(TW(_impl.get(list2tuple(index))));
  }
}

template <class T, class TW>
SEXP RBasicEntity<T, TW>::getScalar() const {
  return Rcpp::wrap(TW(_impl.get()));
}

/*.. method:: Entity.find(index)

  Searches the current entity for an instance with the specified index.

  :return: The wanted entity if found, or ``NULL`` otherwise.
*/
template <class T, class TW>
SEXP RBasicEntity<T, TW>::find(Rcpp::List index) const {
  std::map<ampl::Tuple, T> instances = _impl.getInstances();
  typename std::map<ampl::Tuple, T>::iterator it = instances.find(list2tuple(index));
  if(it != instances.end()) {
    return Rcpp::wrap(TW(it->second));
  } else {
    return R_NilValue;
  }
}

/*.. method:: Entity.getInstances()

  Get all the instances of this entity.

  :return: A list with all the instances of this entity.
*/
template <class T, class TW>
Rcpp::List RBasicEntity<T, TW>::getInstances() const {
  Rcpp::List list;
  std::map<ampl::Tuple, T> instances = _impl.getInstances();
  for(typename std::map<ampl::Tuple, T>::iterator it = instances.begin(); it != instances.end(); it++) {
    list[it->second.name()] = TW(it->second);
  }
  return list;
}

#endif
