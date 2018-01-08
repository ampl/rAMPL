#include "rset_entity.h"
#include "utils.h"
#include <Rcpp.h>
/*.. _secRrefSetEntity:
.. highlight:: r

Set
===

*/

/*.. class:: Set

  Represents an AMPL set. In case of not indexed sets, this class exposes
  iterators for accessing its elements. The members of the set are tuples.
  All these methods throw a TypeError if called for an indexed set.

  In case of indexed sets, you can gain access to the instances using the
  operator [].

  All the accessors in this class throw an RuntimeError if the instance has
  been deleted in the underlying AMPL interpreter.

  Data can be assigned to the set using the methods
  :meth:`~Set.setValues` (for non-indexed sets only) or using
  :meth:`~AMPL.setData` and an object of class
  :class:`~DataFrame`.

*/
RSetEntity::RSetEntity(ampl::Set impl):  RBasicEntity<ampl::SetInstance, RSetInstance>(impl), _impl(impl) { }

/*.. method:: Set.arity()

  The arity of the set, or number of components in each member of this set.

  :return: The arity of the set.
*/
int RSetEntity::arity() const {
  return _impl.arity();
}

/*.. method:: Set.size()

  Get the number of tuples in this set. Valid only for non indexed sets.

  :return: The number of tuples in the set.
*/
int RSetEntity::size() const {
  return _impl.size();
}

/*.. method:: Set.members()

  Get the members of this Set. Valid only for non indexed sets.

  :return: The list of members of the set.
*/
std::vector<Rcpp::List> RSetEntity::members() const {
  std::vector<Rcpp::List> members;
  ampl::SetInstance::MemberRange range = _impl.members();
  for(ampl::SetInstance::MemberRange::iterator it = range.begin(); it != range.end(); it++){
    members.push_back(tuple2list(*it));
  }
  return members;
}

/*.. method:: Set.contains(tuple)

  Check wether this set instance contains the specified tuple.

  :return: `TRUE` if this set instance contains the specified tuple.
*/
bool RSetEntity::contains(Rcpp::List tuple) const {
  return _impl.contains(list2tuple(tuple));
}

/*.. method:: Set.getValues()

  Get values of this set in a data.frame. Valid only for non indexed sets.

  :return: `data.frame` containing the values of this set.
*/
Rcpp::DataFrame RSetEntity::getValues() const {
  return df2rdf(_impl.getValues());
}

/*.. method:: Set.setValues(values)

  Set values. Valid only for non indexed sets.
*/
void RSetEntity::setValues(SEXP values) {
  if(::Rf_inherits(values, "data.frame")) {
    Rcpp::DataFrame df = values;
    df.push_front(Rcpp::Range(1, df.nrows()), "index"); // FIXME: shouldn't be necessary
    _impl.setValues(rdf2df(df));
  } else {
    setValuesList(values);
  }
}

void RSetEntity::setValuesList(const Rcpp::List &values) {
  std::vector<ampl::Tuple> objects(values.size());
  for(int i = 0; i < values.size(); i++){
    objects[i] = list2tuple(values[i]);
  }
  return _impl.setValues(objects.data(), objects.size());
}

// *** RCPP_MODULE ***
RCPP_MODULE(rset_entity){
  Rcpp::class_<RBasicEntity<ampl::SetInstance, RSetInstance> >("SEntity")
    .const_method("name", &RBasicEntity<ampl::SetInstance, RSetInstance>::name)
    .const_method("get", &RBasicEntity<ampl::SetInstance, RSetInstance>::get)
    .const_method("[[", &RBasicEntity<ampl::SetInstance, RSetInstance>::get)
    .const_method("toString", &RBasicEntity<ampl::SetInstance, RSetInstance>::toString)
    ;
  Rcpp::class_<RSetEntity>("Set")
    .derives<RBasicEntity<ampl::SetInstance, RSetInstance> >("SEntity")
    .method("arity", &RSetEntity::arity, "The arity of the set")
    .method("size", &RSetEntity::size, "The number of tuples in the set")
    .method("members", &RSetEntity::members, "The members of the set")
    .method("contains", &RSetEntity::contains, "Check wether this set instance contains the specified tuple")
    .method("getValues", &RSetEntity::getValues)
    .method("setValues", &RSetEntity::setValues, "Set values")
    ;
}
