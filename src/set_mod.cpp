#include "set_mod.h"
#include "utils.h"
#include <Rcpp.h>
/*.. _secRrefAMPL:
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
RcppSet::RcppSet(ampl::Set impl): _impl(impl) { }

/*.. method:: Set.arity()

  The arity of the set, or number of components in each member of this set.

  :return: The arity of the set.
*/
int RcppSet::arity() const {
  return _impl.arity();
}

// *** RCPP_MODULE ***
RCPP_MODULE(set_module){
    Rcpp::class_<RcppSet>( "Set" )
        .method("arity", &RcppSet::arity, "The arity of the set")
        ;
}
