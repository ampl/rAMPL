#include "ampl_mod.h"
#include "utils.h"
#include <Rcpp.h>
/*.. _secRrefAMPL:
.. highlight:: r

AMPL
====

*/

/*.. class:: AMPL

  An AMPL translator.

  An object of this class can be used to do the following tasks:

  - Run AMPL code. See :meth:`~.AMPL.eval` and
    :meth:`~.AMPL.evalAsync`.
  - Read models and data from files. See :meth:`~.AMPL.read`,
    :meth:`~.AMPL.readData`, :meth:`~.AMPL.readAsync`, and
    :meth:`~.AMPL.readDataAsync`.
  - Solve optimization problems constructed from model and data (see
    :meth:`~.AMPL.solve` and :meth:`~.AMPL.solveAsync`).
  - Access single Elements of an optimization problem. See
    :meth:`~.AMPL.getVariable`, :meth:`~.AMPL.getConstraint`,
    :meth:`~.AMPL.getObjective`, :meth:`~.AMPL.getSet`,
    and :meth:`~.AMPL.getParameter`.
  - Access lists of available entities of an optimization problem. See
    :meth:`~.AMPL.getVariables`, :meth:`~.AMPL.getConstraints`,
    :meth:`~.AMPL.getObjectives`, :meth:`~.AMPL.getSets`,
    and :meth:`~.AMPL.getParameters`.

  Error handling is two-faced:

  - Errors coming from the underlying AMPL translator (e.g. syntax errors and
    warnings obtained calling the eval method) are handled by
    the :class:`~amplpy.ErrorHandler` which can be set and get via
    :meth:`~.AMPL.getErrorHandler` and
    :meth:`~.AMPL.setErrorHandler`.
  - Generic errors coming from misusing the API, which are detected in
    R, are thrown as exceptions.

  The default implementation of the error handler throws exceptions on errors
  and prints to console on warnings.

  The output of every user interaction with the underlying translator is
  handled implementing the abstract class :class:`~amplpy.OutputHandler`.
  The (only) method is called at each block of output from the translator.
  The current output handler can be accessed and set via
  :meth:`~.AMPL.getOutputHandler` and
  :meth:`~.AMPL.setOutputHandler`.


  :param env: The AMPL environment (optional). This allows the user to specify
    the location of the AMPL binaries to be used and to modify the environment
    variables in which the AMPL interpreter will run.
  :type env: :py:class:`Environemnt`
  :raises Error: If no valid AMPL license has been found or if the translator
    cannot be started for any other reason.
*/
RcppAMPL::RcppAMPL() { }
RcppAMPL::RcppAMPL(SEXP s): _impl(getObj<RcppEnvironment>("Environment", s)->_impl) { }

/*.. method:: AMPL.cd(path = NULL)

  Change or display the current working directory (see
  https://en.wikipedia.org/wiki/Working_directory).

  :param str path:  New working directory or null (to display the working directory).
  :type path: str or ``NULL``
  :return: The current working directory.
*/
Rcpp::String RcppAMPL::cd(){
  return _impl.cd();
}
Rcpp::String RcppAMPL::cdStr(std::string path){
  return _impl.cd(path);
}

/*.. method:: AMPL.setOption(name, value)

  Set an AMPL option to a specified value.

  :param str name: Name of the option to be set (alphanumeric without spaces).
  :param str value: String representing the value the option must be set to.
  :return: ``NULL``
  :raises Error: If the option name is not valid.
*/
void RcppAMPL::setOption(std::string name, std::string value){
  _impl.setOption(name, value);
}

/*.. method:: AMPL.getOption(name)

  Get the current value of the specified option. If the option does not
  exist, the returned Optional object will not have value.

  :param str name: Option name (alphanumeric)
  :return: Value of the option as a string or ``NA``.
  :raises Error: If the option name is not valid.
*/
Rcpp::String RcppAMPL::getOption(std::string name){
  if (ampl::Optional<std::string> value = _impl.getOption(name)) {
    return *value;
  } else {
    return NA_STRING;
  }
}

/*.. method:: AMPL.read(fileName)

  Interprets the specified file (script or model or mixed). As a side effect,
  it invalidates all entities (as the passed file can contain any arbitrary
  command); the lists of entities will be re-populated lazily (at first
  access)

  :param str fileName: Full path to the file.
  :return: ``NULL``
  :raises Error: In case the file does not exist.
*/
void RcppAMPL::read(std::string fileName){
  _impl.read(fileName);
}

/*.. method:: AMPL.readData(fileName)

  Interprets the specified file as an AMPL data file. As a side effect, it
  invalidates all entities (as the passed file can contain any arbitrary
  command); the lists of entities will be re-populated lazily (at first
  access). After reading the file, the interpreter is put back to "model"
  mode.

  :param str filName: Full path to the file.
  :return: ``NULL``
  :raises Error: In case the file does not exist.
*/
void RcppAMPL::readData(std::string fileName){
  _impl.readData(fileName);
}

/*.. method:: AMPL.eval(amplstatements)

  Parses AMPL code and evaluates it as a possibly empty sequence of AMPL
  declarations and statements.

  As a side effect, it invalidates all entities (as the passed statements
  can contain any arbitrary command); the lists of entities will be
  re-populated lazily (at first access)

  The output of interpreting the statements is passed to the current
  OutputHandler (see :meth:`~.AMPL.getOutputHandler` and
  :meth:`~.AMPL.setOutputHandler`).

  By default, errors are reported as exceptions and warnings are printed on
  stdout. This behavior can be changed reassigning an
  ErrorHandler using setErrorHandler.

  :param str amplstatements: A collection of AMPL statements and declarations
    to be passed to the interpreter.
  :return: ``NULL``
  :raises Error: if the input is not a complete AMPL statement (e.g.
    if it does not end with semicolon) or if the underlying
    interpreter is not running
*/
void RcppAMPL::eval(std::string amplstatements) {
  return _impl.eval(amplstatements);
}

/*.. method:: AMPL.solve()

  Solve the current model.

  :return: ``NULL``.
  :raises Error: If the underlying interpreter is not running.
*/
void RcppAMPL::solve() {
  return _impl.solve();
}

/*.. method:: AMPL.getVariable(name)

  Get the variable with the corresponding name.

  :param str name: Name of the variable to be found.
  :return: Variable object.
  :rtype: :class:`Variable`
  :raises Error: If the specified variable does not exist.
*/
RcppVariable RcppAMPL::getVariable(std::string name) const {
  return RcppVariable(_impl.getVariable(name));
}

/*.. method:: AMPL.getConstraint(name)

  Get the constraint with the corresponding name.

  :param str name: Name of the constraint to be found.
  :return: Constraint object.
  :rtype: :class:`Variable`
  :raises Error: If the specified constraint does not exist.
*/
RcppConstraint RcppAMPL::getConstraint(std::string name) const {
  return RcppConstraint(_impl.getConstraint(name));
}

/*.. method:: AMPL.getObjective(name)

  Get the objective with the corresponding name.

  :param str name: Name of the objective to be found.
  :return: Objective object.
  :rtype: :class:`Objective`
  :raises Error: If the specified objective does not exist.
*/
RcppObjective RcppAMPL::getObjective(std::string name) const {
  return RcppObjective(_impl.getObjective(name));
}

/*.. method:: AMPL.getSet(name)

  Get the set with the corresponding name.

  :param str name: Name of the set to be found.
  :return: Set object.
  :rtype: :class:`Set`
  :raises Error: If the specified set does not exist.
*/
RcppSet RcppAMPL::getSet(std::string name) const {
  return RcppSet(_impl.getSet(name));
}

/*.. method:: AMPL.getParameter(name)

  Get the parameter with the corresponding name.

  :param str name: Name of the parameter to be found.
  :return: Parameter object.
  :rtype: :class:`Parameter`
  :raises Error: If the specified parameter does not exist.
*/
RcppParameter RcppAMPL::getParameter(std::string name) const {
  return RcppParameter(_impl.getParameter(name));
}


/*.. method:: AMPL.getVariables()

  Get all the variables declared.

  :return: List of :class:`Variable` objects.
*/
Rcpp::List RcppAMPL::getVariables() const {
  Rcpp::List list;
  const ampl::EntityMap<ampl::Variable> map = _impl.getVariables();
  ampl::EntityMap<ampl::Variable>::iterator begin = map.begin();
  ampl::EntityMap<ampl::Variable>::iterator end = map.end();
  for(ampl::EntityMap<ampl::Variable>::iterator itr = begin; itr != end; itr++){
    list[itr->name()] = RcppVariable(*itr);
  }
  return list;
}

/*.. method:: AMPL.getConstraints()

  Get all the constraints declared.

  :return: List of :class:`Constraint` objects.
*/
Rcpp::List RcppAMPL::getConstraints() const {
  Rcpp::List list;
  const ampl::EntityMap<ampl::Constraint> map = _impl.getConstraints();
  ampl::EntityMap<ampl::Constraint>::iterator begin = map.begin();
  ampl::EntityMap<ampl::Constraint>::iterator end = map.end();
  for(ampl::EntityMap<ampl::Constraint>::iterator itr = begin; itr != end; itr++){
    list[itr->name()] = RcppConstraint(*itr);
  }
  return list;
}

/*.. method:: AMPL.getObjectives()

  Get all the objectives declared.

  :return: List of :class:`Objective` objects.
*/
Rcpp::List RcppAMPL::getObjectives() const {
  Rcpp::List list;
  const ampl::EntityMap<ampl::Objective> map = _impl.getObjectives();
  ampl::EntityMap<ampl::Objective>::iterator begin = map.begin();
  ampl::EntityMap<ampl::Objective>::iterator end = map.end();
  for(ampl::EntityMap<ampl::Objective>::iterator itr = begin; itr != end; itr++){
    list[itr->name()] = RcppObjective(*itr);
  }
  return list;
}

/*.. method:: AMPL.getSets()

  Get all the sets declared.

  :return: List of :class:`Set` objects.
*/
Rcpp::List RcppAMPL::getSets() const {
  Rcpp::List list;
  const ampl::EntityMap<ampl::Set> map = _impl.getSets();
  ampl::EntityMap<ampl::Set>::iterator begin = map.begin();
  ampl::EntityMap<ampl::Set>::iterator end = map.end();
  for(ampl::EntityMap<ampl::Set>::iterator itr = begin; itr != end; itr++){
    list[itr->name()] = RcppSet(*itr);
  }
  return list;
}

/*.. method:: AMPL.getParameters()

  Get all the parameters declared.

  :return: List of :class:`Parameter` objects.
*/
Rcpp::List RcppAMPL::getParameters() const {
  Rcpp::List list;
  const ampl::EntityMap<ampl::Parameter> map = _impl.getParameters();
  ampl::EntityMap<ampl::Parameter>::iterator begin = map.begin();
  ampl::EntityMap<ampl::Parameter>::iterator end = map.end();
  for(ampl::EntityMap<ampl::Parameter>::iterator itr = begin; itr != end; itr++){
    list[itr->name()] = RcppParameter(*itr);
  }
  return list;
}

/*.. method:: AMPL.setOutputHandler(outputhandler)

  Sets a new output handler.

  :param function outputhandler: The function handling the AMPL output derived from interpreting user commands.
  :return: ``NULL``.
*/
void RcppAMPL::setOutputHandler(Rcpp::Function outputhandler) {
  free(OHandler);
  OHandler = new AMPLOutputHandler(outputhandler);
  _impl.setOutputHandler(OHandler);
}

/*.. method:: AMPL.getOutputHandler()

  Get the current output handler.

  :return: The current output handler.
  :rtype: function
  :raises Error: If no output handler was set.
*/
Rcpp::Function RcppAMPL::getOutputHandler() const {
  if(OHandler != NULL) {
    return OHandler->outputhandler;
  } else {
    throw Rcpp::exception("No output handler defined.");
  }
}

/*.. method:: AMPL.setErrorHandler(errorhandler)

  Sets a new error handler. The error handler receives a list with:
  - ``$type``: type (warning or error);
  - ``$filename``: name of the file where the error was detected;
  - ``$line``: the row where the error is located;
  - ``$offset``: the offset where the error is located;
  - ``$message``: the error message.

  :param function errorhandler: The function handling AMPL errors and warnings.
  :return: ``NULL``.
*/
void RcppAMPL::setErrorHandler(Rcpp::Function errorhandler) {
  free(EHandler);
  EHandler = new AMPLErrorHandler(errorhandler);
  _impl.setErrorHandler(EHandler);
}

/*.. method:: AMPL.getErrorHandler()

  Get the current error handler.

  :return: The current error handler.
  :rtype: function
  :raises Error: If no error handler was set.
*/
Rcpp::Function RcppAMPL::getErrorHandler() const {
  if(EHandler != NULL) {
    return EHandler->errorhandler;
  } else {
    throw Rcpp::exception("No error handler defined.");
  }
}

// *** RCPP_MODULE ***
RCPP_MODULE(ampl_module){
    Rcpp::class_<RcppAMPL>( "AMPL" )
        .constructor("An AMPL translator")
        .constructor<SEXP>("An AMPL translator")

        .method("cd", &RcppAMPL::cd, "Display the current working directory")
        .method("cd", &RcppAMPL::cdStr, "Change the current working directory")

        .method("getOption", &RcppAMPL::getOption, "Get the current value of the specified option")
        .method("setOption", &RcppAMPL::setOption, "Set an AMPL option to a specified value")

        .method("read", &RcppAMPL::read, "Interprets the specified file")
        .method("readData", &RcppAMPL::readData, "Interprets the specified file as an AMPL data file")

        .method("eval", &RcppAMPL::eval, "Parses AMPL code and evaluates it")
        .method("solve", &RcppAMPL::solve, "Solve the current model")

        .method("getVariable", &RcppAMPL::getVariable, "Get the variable with the corresponding name")
        .method("getConstraint", &RcppAMPL::getConstraint, "Get the constraint with the corresponding name")
        .method("getObjective", &RcppAMPL::getObjective, "Get the objective with the corresponding name")
        .method("getSet", &RcppAMPL::getSet, "Get the set with the corresponding name")
        .method("getParameter", &RcppAMPL::getParameter, "Get the parameter with the corresponding name")

        .method("getVariables", &RcppAMPL::getVariables, "Get all the variables declared")
        .method("getConstraints", &RcppAMPL::getConstraints, "Get all the constraints declared")
        .method("getObjectives", &RcppAMPL::getObjectives, "Get all the objectives declared")
        .method("getSets", &RcppAMPL::getSets, "Get all the sets declared")
        .method("getParameters", &RcppAMPL::getParameters, "Get all the parameters declared")

        .method("setOutputHandler", &RcppAMPL::setOutputHandler, "Sets a new output handler")
        .method("getOutputHandler", &RcppAMPL::getOutputHandler, "Get the current output handler")
        .method("setErrorHandler", &RcppAMPL::setErrorHandler, "Sets a new error handler")
        .method("getErrorHandler", &RcppAMPL::getErrorHandler, "Get the current error handler")
        ;
}
