#include "robj_entity.h"
#include "utils.h"
#include <Rcpp.h>
/*.. _secRrefObjEntity:
.. highlight:: r

Objective
=========

*/

/*.. class:: Objective

  Represents an AMPL objective. Note that, in case of a scalar objective, all
  the properties (corresponding to AMPL suffixes) of the objective instance
  can be accessed through methods like :meth:`~.Objective.value`.
  The methods have the same name of the corresponding AMPL suffixes.
  See http://www.ampl.com/NEW/suffbuiltin.html for a list of the available
  suffixes.

  All these methods throw an error if called on an entity which has been deleted
  in the underlying intepreter.

  To gain access to all the values in an entity (for all instances and all
  suffixes for that entities), see :meth:`~.Entity.getValues` and the
  :class:`DataFrame` class.
*/
RObjectiveEntity::RObjectiveEntity(ampl::Objective impl): RBasicEntity<ampl::ObjectiveInstance, RObjectiveInstance>(impl), _impl(impl) { }

/*.. method:: Objective.value()

  Get the value of the objective instance.

  :return: Value of the objective.
*/
double RObjectiveEntity::value() const {
  return _impl.value();
}


/*.. method:: Objective.astatus()

  Return the AMPL status.

  :return: The AMPL status.
*/
std::string RObjectiveEntity::astatus() const {
  return _impl.astatus();
}

/*.. method:: Objective.sstatus()

  Return the solver status.

  :return: The solver status.
*/
std::string RObjectiveEntity::sstatus() const {
  return _impl.sstatus();
}

/*.. method:: Objective.exitcode()

  Exit code returned by the solver after most recent solve with this objective.

  :return: The exit code returned by the solver.
*/
int RObjectiveEntity::exitcode() const {
  return _impl.exitcode();
}

/*.. method:: Objective.message()

  Result message returned by solver after most recent solve with this objective.

  :return: The result message returned by the solver.
*/
std::string RObjectiveEntity::message() const {
  return _impl.message();
}

/*.. method:: Objective.result()

  Result string returned by solver after most recent solve with this objective.

  :return: The result message returned by the solver.
*/
std::string RObjectiveEntity::result() const {
  return _impl.result();
}

/*.. method:: Objective.drop()

  Drop this objective.
*/
void RObjectiveEntity::drop() {
  return _impl.drop();
}

/*.. method:: Objective.restore()

  Restore this objective  (if it had been dropped, no effect otherwise)
*/
void RObjectiveEntity::restore() {
  return _impl.restore();
}

/*.. method:: Objective.message()

  Get the sense of this objective

  :return: ``TRUE`` if minimize, ``FALSE`` if maximize.
*/
bool RObjectiveEntity::minimization() const {
  return _impl.minimization();
}

// *** RCPP_MODULE ***
RCPP_MODULE(robj_entity){
  Rcpp::class_<RBasicEntity<ampl::ObjectiveInstance, RObjectiveInstance> >("OEntity")
    .const_method("name", &RBasicEntity<ampl::ObjectiveInstance, RObjectiveInstance>::name)
    .const_method("get", &RBasicEntity<ampl::ObjectiveInstance, RObjectiveInstance>::get)
    .const_method("[[", &RBasicEntity<ampl::ObjectiveInstance, RObjectiveInstance>::get)
    .const_method("getValues", &RBasicEntity<ampl::ObjectiveInstance, RObjectiveInstance>::getValues)
    .const_method("toString", &RBasicEntity<ampl::ObjectiveInstance, RObjectiveInstance>::toString)
    ;
  Rcpp::class_<RObjectiveEntity>("Objective")
    .derives<RBasicEntity<ampl::ObjectiveInstance, RObjectiveInstance> >("OEntity")
    .method("value", &RObjectiveEntity::value, "Get the value of the objective instance")
    .method("astatus", &RObjectiveEntity::astatus, "Return the AMPL status")
    .method("sstatus", &RObjectiveEntity::sstatus, "Return the solver status")
    .method("exitcode", &RObjectiveEntity::exitcode, "Exit code returned by solver after most recent solve with this objective")
    .method("message", &RObjectiveEntity::message, "Result message returned by the solver")
    .method("result", &RObjectiveEntity::value, "Result string returned by the solver")
    .method("drop", &RObjectiveEntity::drop, "Drop this objective")
    .method("restore", &RObjectiveEntity::restore, "Restore this objective")
    .method("minimization", &RObjectiveEntity::minimization, "Get the sense of this objective")
    ;
}
