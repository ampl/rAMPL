#include "constraint_mod.h"
#include "utils.h"
#include <Rcpp.h>
/*.. _secRrefAMPL:
.. highlight:: r

Constraint
==========

*/

/*.. class:: Constraint

  This class represents an algebraic or logical constraint. In case the
  constraint is scalar, its values can be accessed via functions like
  :meth:`~.Constraint.body` and :meth:`~.Constraint.dual`.
  All the AMPL suffixes for constraints (see
  http://www.ampl.com/NEW/suffbuiltin.html)
  are available through methods of this class with the same name (and methods
  of ConstraintInstance for indexed constraints).

  Note that, since this class represents both algebraic and logical
  constraints, some suffixes might not be available for every entity.

  An TypeError is thrown if one of such methods is called for
  a non-scalar constraint and if a method corresponding to a suffix which is
  not supported by the type of the constraint is called.
  A runtime error is thrown if any property of an entity which has been
  deleted from the underlying interpreter is accessed.

  To gain access to all the values in an entity (for all instances and all
  suffixes for that entities), see :meth:`~.Entity.getValues` and
  the :class:`DataFrame` class.
*/
RcppConstraint::RcppConstraint(ampl::Constraint impl): _impl(impl) { }

/*.. method:: Constraint.isLogical()

  Check if the constraint is a logical constraint. The available suffixes
  differ between logical and non logical constraints. See
  http://www.ampl.com/NEW/suffbuiltin.html for a list of the available
  suffixes for algebraic constraints. The suffixes available for logical
  constraints are marked on the method description by "Valid only for logical
  constraints".

  :return: ``TRUE`` if logical
*/
bool RcppConstraint::isLogical() const {
  return _impl.isLogical();
}

// *** RCPP_MODULE ***
RCPP_MODULE(constraint_module){
    Rcpp::class_<RcppConstraint>( "Constraint" )
        .method("isLogical", &RcppConstraint::isLogical, "Check if the constraint is a logical constraint")
        ;
}

