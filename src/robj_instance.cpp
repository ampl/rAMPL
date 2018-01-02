#include "robj_instance.h"
#include "utils.h"
#include <Rcpp.h>
/*.. _secRrefAMPL:
.. highlight:: r

ObjectiveInstance
=================

*/

/*.. class:: ObjectiveInstance

  Represents an AMPL objective. Note that, in case of a scalar objective, all
  the properties (corresponding to AMPL suffixes) of the objective instance
  can be accessed through methods like :meth:`~.ObjectiveInstance.value`.
  The methods have the same name of the corresponding AMPL suffixes.
  See http://www.ampl.com/NEW/suffbuiltin.html for a list of the available
  suffixes.

  All these methods throw an error if called on an entity which has been deleted
  in the underlying intepreter.

  To gain access to all the values in an entity (for all instances and all
  suffixes for that entities), see :meth:`~.Entity.getValues` and the
  :class:`DataFrame` class.
*/
RObjectiveInstance::RObjectiveInstance(ampl::ObjectiveInstance impl): _impl(impl) { }

/*.. method:: ObjectiveInstance.value()

  Get the value of the objective instance.

  :return: Value of the objective.
*/
double RObjectiveInstance::value() const {
  return _impl.value();
}


/*.. method:: ObjectiveInstance.astatus()

  Return the AMPL status.

  :return: The AMPL status.
*/
std::string RObjectiveInstance::astatus() const {
  return _impl.astatus();
}

/*.. method:: ObjectiveInstance.sstatus()

  Return the solver status.

  :return: The solver status.
*/
std::string RObjectiveInstance::sstatus() const {
  return _impl.sstatus();
}

/*.. method:: ObjectiveInstance.exitcode()

  Exit code returned by the solver after most recent solve with this objective.

  :return: The exit code returned by the solver.
*/
int RObjectiveInstance::exitcode() const {
  return _impl.exitcode();
}

/*.. method:: ObjectiveInstance.message()

  Result message returned by solver after most recent solve with this objective.

  :return: The result message returned by the solver.
*/
std::string RObjectiveInstance::message() const {
  return _impl.message();
}

/*.. method:: ObjectiveInstance.result()

  Result string returned by solver after most recent solve with this objective.

  :return: The result message returned by the solver.
*/
std::string RObjectiveInstance::result() const {
  return _impl.result();
}

/*.. method:: ObjectiveInstance.drop()

  Drop this objective.
*/
void RObjectiveInstance::drop() {
  return _impl.drop();
}

/*.. method:: ObjectiveInstance.restore()

  Restore this objective  (if it had been dropped, no effect otherwise)
*/
void RObjectiveInstance::restore() {
  return _impl.restore();
}

/*.. method:: ObjectiveInstance.message()

  Get the sense of this objective

  :return: ``TRUE`` if minimize, ``FALSE`` if maximize.
*/
bool RObjectiveInstance::minimization() const {
  return _impl.minimization();
}

// *** RCPP_MODULE ***
RCPP_MODULE(robj_instance){
  Rcpp::class_<RObjectiveInstance>( "ObjectiveInstance" )
    .method("value", &RObjectiveInstance::value, "Get the value of the objective instance")
    .method("astatus", &RObjectiveInstance::astatus, "Return the AMPL status")
    .method("sstatus", &RObjectiveInstance::sstatus, "Return the solver status")
    .method("exitcode", &RObjectiveInstance::exitcode, "Exit code returned by solver after most recent solve with this objective")
    .method("message", &RObjectiveInstance::message, "Result message returned by the solver")
    .method("result", &RObjectiveInstance::value, "Result string returned by the solver")
    .method("drop", &RObjectiveInstance::drop, "Drop this objective")
    .method("restore", &RObjectiveInstance::restore, "Restore this objective")
    .method("minimization", &RObjectiveInstance::minimization, "Get the sense of this objective")
    ;
}
