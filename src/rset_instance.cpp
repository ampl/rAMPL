#include "rset_instance.h"
#include "utils.h"
#include <Rcpp.h>
/*.. _secRrefSetInstance:
.. highlight:: r

SetInstance
===========

*/

/*.. class:: SetInstance


*/
RSetInstance::RSetInstance(ampl::SetInstance impl): _impl(impl) { }

/*.. method:: SetInstance.name()

  Returns the name of this instance.

  :return: Name of the instance.
*/
std::string RSetInstance::name() const {
  return _impl.name();
}

/*.. method:: SetInstance.toString()

  Returns a string representation of this instance.

  :return: String representation of this instance.
*/
std::string RSetInstance::toString() const {
  return _impl.toString();
}

/*.. method:: SetInstance.size()

  Get the number of tuples in this set. Valid only for non indexed sets.

  :return: The number of tuples in the set.
*/
int RSetInstance::size() { //const {
  return _impl.size();
}

/*.. method:: SetInstance.members()

  Get the members of this Set. Valid only for non indexed sets.

  :return: The list of members of the set.
*/
std::vector<Rcpp::List> RSetInstance::members() { //const {
  std::vector<Rcpp::List> members;
  ampl::SetInstance::MemberRange range = _impl.members();
  for(ampl::SetInstance::MemberRange::iterator it = range.begin(); it != range.end(); it++){
    members.push_back(tuple2list(*it));
  }
  return members;
}

/*.. method:: SetInstance.contains(tuple)

  Check wether this set instance contains the specified tuple.

  :return: `TRUE` if this set instance contains the specified tuple.
*/
bool RSetInstance::contains(Rcpp::List tuple) const {
  return _impl.contains(list2tuple(tuple));
}

/*.. method:: SetInstance.getValues()

  Get values of this set in a data.frame. Valid only for non indexed sets.

  :return: `data.frame` containing the values of this set.
*/
Rcpp::DataFrame RSetInstance::getValues() const {
  return df2rdf(_impl.getValues());
}

/*.. method:: SetInstance.setValues(values)

  Set values. Valid only for non indexed sets.
*/
void RSetInstance::setValues(SEXP values) {
  if(::Rf_inherits(values, "data.frame")) {
    Rcpp::DataFrame df = values;
    df.push_front(Rcpp::Range(1, df.nrows()), "index"); // FIXME: shouldn't be necessary
    _impl.setValues(rdf2df(df));
  } else {
    setValuesList(values);
  }
}

void RSetInstance::setValuesList(Rcpp::List values) {
  std::vector<ampl::Tuple> objects(values.size());
  for(int i = 0; i < values.size(); i++){
    objects[i] = list2tuple(values[i]);
  }
  return _impl.setValues(objects.data(), objects.size());
}

// *** RCPP_MODULE ***
RCPP_MODULE(rset_instance){
  Rcpp::class_<RSetInstance>("SetInstance")
    .method("name", &RSetInstance::name)
    .method("toString", &RSetInstance::toString)
    .method("size", &RSetInstance::size, "The number of tuples in the set")
    .method("members", &RSetInstance::members, "The members of the set")
    .method("contains", &RSetInstance::contains, "Check wether this set instance contains the specified tuple")
    .method("getValues", &RSetInstance::getValues, "Get values")
    .method("setValues", &RSetInstance::setValues, "Set values")
    ;
}
