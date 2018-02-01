#include "rampl.h"
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

.. function:: AMPL()

  Default constructor.

  :raises Error: If no valid AMPL license has been found or if the translator
    cannot be started for any other reason.

.. function:: AMPL(environment)

  Constructor: creates a new AMPL instance with the specified environment.
  This allows the user to specify the location of the AMPL binaries to be used
  and to modify the environment variables in which the AMPL interpreter will
  run.

  :param env: The AMPL environment.
  :type env: :py:class:`Environment`
  :raises Error: If no valid AMPL license has been found or if the translator
    cannot be started for any other reason.
*/
RAMPL::RAMPL() { }
RAMPL::RAMPL(SEXP s): _impl(getObj<REnvironment>("Environment", s)->_impl) { }

/*.. method:: AMPL.toString()

  Get a string describing the object. Returns the version of the API and
  either the version of the interpreter or the message "AMPL is not
  running" if the interpreter is not running (e.g. due to unexpected
  internal error or to a call AMPL::close)

  :return: A string that represents this object.
*/
Rcpp::String RAMPL::toString() const {
  return _impl.toString();
}

/*.. method:: AMPL.cd(path = NULL)

  Change or display the current working directory (see
  https://en.wikipedia.org/wiki/Working_directory).

  :param str path:  New working directory or null (to display the working directory).
  :type path: str or ``NULL``
  :return: The current working directory.
*/
Rcpp::String RAMPL::cd(){
  return _impl.cd();
}
Rcpp::String RAMPL::cdStr(std::string path){
  return _impl.cd(path);
}

/*.. method:: AMPL.setOption(name, value)

  Set an AMPL option to a specified value.

  :param str name: Name of the option to be set (alphanumeric without spaces).
  :param value: string/number/boolean representing the value the option must be set to.
  :return: ``NULL``
  :raises Error: If the option name is not valid.
*/
void RAMPL::setOption(std::string name, SEXP value){
  switch(TYPEOF(value)) {
    case REALSXP:
      _impl.setDblOption(name, Rcpp::as<double>(value));
      break;
    case LGLSXP:
      _impl.setBoolOption(name, Rcpp::as<bool>(value));
      break;
    case STRSXP:
      _impl.setOption(name, Rcpp::as<std::string>(value));
      break;
    default:
      Rcpp::stop("invalid type");
  }
}

/*.. method:: AMPL.getOption(name)

  Get the current value of the specified option. If the option does not
  exist, returns ``NA``.

  :param str name: Option name (alphanumeric)
  :return: Value of the option as a string or ``NA``.
  :raises Error: If the option name is not valid.
*/
Rcpp::String RAMPL::getOption(std::string name) const {
  if (ampl::Optional<std::string> value = _impl.getOption(name)) {
    return *value;
  } else {
    return NA_STRING;
  }
}


/*.. method:: AMPL.getDblOption(name)

  Get the current value of the specified double option. If the option does not
  exist, returns ``NA``.

  :param str name: Option name (alphanumeric)
  :return: Value of the option as numeric or ``NA``.
  :raises Error: If the option name is not valid, or if the value could not be casted.
*/
double RAMPL::getDblOption(std::string name) const {
  if (ampl::Optional<double> value = _impl.getDblOption(name)) {
    return *value;
  } else {
    return NA_REAL;
  }
}

/*.. method:: AMPL.getIntOption(name)

  Get the current value of the specified integer option. If the option does not
  exist, returns ``NA``.

  :param str name: Option name (alphanumeric)
  :return: Value of the option as numeric or ``NA``.
  :raises Error: If the option name is not valid, or if the value could not be casted.
*/
int RAMPL::getIntOption(std::string name) const {
  if (ampl::Optional<int> value = _impl.getIntOption(name)) {
    return *value;
  } else {
    return NA_INTEGER;
  }
}

/*.. method:: AMPL.getBoolOption(name)

  Get the current value of the specified boolean option. If the option does not
  exist, returns ``NA``.

  :param str name: Option name (alphanumeric)
  :return: Value of the option as boolean or ``NA``.
  :raises Error: If the option name is not valid, or if the value could not be casted.
*/
bool RAMPL::getBoolOption(std::string name) const {
  if (ampl::Optional<bool> value = _impl.getBoolOption(name)) {
    return *value;
  } else {
    return NA_LOGICAL;
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
void RAMPL::read(std::string fileName){
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
void RAMPL::readData(std::string fileName) {
  _impl.readData(fileName);
}

/*.. method:: AMPL.readTable(tableName)

  Read the table corresponding to the specified name, equivalent to the AMPL statement:

  .. code-block:: ampl

    read table tableName;


  :param string tableName: Name of the table to be read.
*/
void RAMPL::readTable(std::string tableName) {
  _impl.readTable(tableName);
}

/*.. method:: AMPL.writeTable(tableName)

  Write the table corresponding to the specified name, equivalent to the AMPL statement:

  .. code-block:: ampl

    write table tableName;

  :param string tableName: Name of the table to be written.
*/
void RAMPL::writeTable(std::string tableName) {
  _impl.writeTable(tableName);
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
void RAMPL::eval(std::string amplstatements) {
  return _impl.eval(amplstatements);
}


/*.. method:: AMPL.reset()

  Clears all entities in the underlying %AMPL interpreter, clears all maps
  and invalidates all entities.
*/
void RAMPL::reset() {
  return _impl.reset();
}


/*.. method:: AMPL.close()

  Stops the underlying engine, and release all any further attempt to execute
  optimisation commands without restarting it will throw an exception.
*/
void RAMPL::close() {
  return _impl.close();
}

/*.. method:: AMPL.isRunning()

  Returns ``TRUE``  if the underlying engine is running.
*/
bool RAMPL::isRunning() const {
  return _impl.isRunning();
}

/*.. method:: AMPL.solve()

  Solve the current model.

  :return: ``NULL``.
  :raises Error: If the underlying interpreter is not running.
*/
void RAMPL::solve() {
  return _impl.solve();
}


/*.. method:: AMPL.getData(statements)
  Get the data corresponding to the display statements. The statements can
  be AMPL expressions, or entities. It captures the equivalent of the
  command:

  .. code-block:: ampl

    display ds1, ..., dsn;


  where ``ds1, ..., dsn`` are the ``statements`` with which the function is called.

  As only one DataFrame is returned, the operation will fail if the results
  of the display statements cannot be indexed over the same set. As a
  result, any attempt to get data from more than one set, or to get data
  for multiple parameters with a different number of indexing sets will
  fail.

  :param list statements: The display statements to be fetched.
  :return: DataFrame capturing the output of the display command in tabular form.
  :rtype: DataFrame
  :raises Error: if the AMPL visualization command does not succeed for one of the reasons listed above.
*/
Rcpp::DataFrame RAMPL::getData(Rcpp::List statements) const {
  std::vector<const char *> tmp(statements.size());
  for(int i = 0; i < statements.size(); i++) {
    tmp[i] = Rcpp::as<const char *>(statements[i]);
  }
  return df2rdf(_impl.getData(ampl::StringArgs(tmp.data(), tmp.size())));
}

/*.. method:: AMPL.getValue(scalarExpression)

  Get a scalar value from the underlying %AMPL interpreter, as a double or a string.
  :param string scalarExpression: An AMPL expression which evaluates to a scalar value.
  :return: The value of the expression.
*/
SEXP RAMPL::getValue(std::string scalarExpression) const {
  return variant2sexp(_impl.getValue(scalarExpression));
}

/*.. method:: AMPL.setData(df, numberOfIndexColumns, setName)

  Assign the data in the dataframe to the AMPL entities with the names
  corresponding to the column names. If setName is ``NULL``, only the
  parameters value will be assigned.

  :param DataFrame df: The dataframe containing the data to be assigned.
  :param integer numberOfIndexColumns: Number of index columns.
  :param string setName:  The name of the set to which the indices values of the DataFrame are to be assigned.
  :raises Error: If the data assignment procedure was not successful.
*/
void RAMPL::setData(const Rcpp::DataFrame &rdf, int numberOfIndexColumns = 1, std::string setName = "") {
  _impl.setData(rdf2df(rdf, numberOfIndexColumns), setName);
}

/*.. method:: AMPL.getVariable(name)

  Get the variable with the corresponding name.

  :param str name: Name of the variable to be found.
  :return: Variable object.
  :rtype: :class:`Variable`
  :raises Error: If the specified variable does not exist.
*/
RVariableEntity RAMPL::getVariable(std::string name) const {
  return RVariableEntity(_impl.getVariable(name));
}

/*.. method:: AMPL.getConstraint(name)

  Get the constraint with the corresponding name.

  :param str name: Name of the constraint to be found.
  :return: Constraint object.
  :rtype: :class:`Variable`
  :raises Error: If the specified constraint does not exist.
*/
RConstraintEntity RAMPL::getConstraint(std::string name) const {
  return RConstraintEntity(_impl.getConstraint(name));
}

/*.. method:: AMPL.getObjective(name)

  Get the objective with the corresponding name.

  :param str name: Name of the objective to be found.
  :return: Objective object.
  :rtype: :class:`Objective`
  :raises Error: If the specified objective does not exist.
*/
RObjectiveEntity RAMPL::getObjective(std::string name) const {
  return RObjectiveEntity(_impl.getObjective(name));
}

/*.. method:: AMPL.getSet(name)

  Get the set with the corresponding name.

  :param str name: Name of the set to be found.
  :return: Set object.
  :rtype: :class:`Set`
  :raises Error: If the specified set does not exist.
*/
RSetEntity RAMPL::getSet(std::string name) const {
  return RSetEntity(_impl.getSet(name));
}

/*.. method:: AMPL.getParameter(name)

  Get the parameter with the corresponding name.

  :param str name: Name of the parameter to be found.
  :return: Parameter object.
  :rtype: :class:`Parameter`
  :raises Error: If the specified parameter does not exist.
*/
RParameterEntity RAMPL::getParameter(std::string name) const {
  return RParameterEntity(_impl.getParameter(name));
}


/*.. method:: AMPL.getVariables()

  Get all the variables declared.

  :return: List of :class:`Variable` objects.
*/
Rcpp::List RAMPL::getVariables() const {
  Rcpp::List list;
  const ampl::EntityMap<ampl::Variable> map = _impl.getVariables();
  ampl::EntityMap<ampl::Variable>::iterator begin = map.begin();
  ampl::EntityMap<ampl::Variable>::iterator end = map.end();
  for(ampl::EntityMap<ampl::Variable>::iterator itr = begin; itr != end; itr++){
    list[itr->name()] = RVariableEntity(*itr);
  }
  return list;
}

/*.. method:: AMPL.getConstraints()

  Get all the constraints declared.

  :return: List of :class:`Constraint` objects.
*/
Rcpp::List RAMPL::getConstraints() const {
  Rcpp::List list;
  const ampl::EntityMap<ampl::Constraint> map = _impl.getConstraints();
  ampl::EntityMap<ampl::Constraint>::iterator begin = map.begin();
  ampl::EntityMap<ampl::Constraint>::iterator end = map.end();
  for(ampl::EntityMap<ampl::Constraint>::iterator itr = begin; itr != end; itr++){
    list[itr->name()] = RConstraintEntity(*itr);
  }
  return list;
}

/*.. method:: AMPL.getObjectives()

  Get all the objectives declared.

  :return: List of :class:`Objective` objects.
*/
Rcpp::List RAMPL::getObjectives() const {
  Rcpp::List list;
  const ampl::EntityMap<ampl::Objective> map = _impl.getObjectives();
  ampl::EntityMap<ampl::Objective>::iterator begin = map.begin();
  ampl::EntityMap<ampl::Objective>::iterator end = map.end();
  for(ampl::EntityMap<ampl::Objective>::iterator itr = begin; itr != end; itr++){
    list[itr->name()] = RObjectiveEntity(*itr);
  }
  return list;
}

/*.. method:: AMPL.getSets()

  Get all the sets declared.

  :return: List of :class:`Set` objects.
*/
Rcpp::List RAMPL::getSets() const {
  Rcpp::List list;
  const ampl::EntityMap<ampl::Set> map = _impl.getSets();
  ampl::EntityMap<ampl::Set>::iterator begin = map.begin();
  ampl::EntityMap<ampl::Set>::iterator end = map.end();
  for(ampl::EntityMap<ampl::Set>::iterator itr = begin; itr != end; itr++){
    list[itr->name()] = RSetEntity(*itr);
  }
  return list;
}

/*.. method:: AMPL.getParameters()

  Get all the parameters declared.

  :return: List of :class:`Parameter` objects.
*/
Rcpp::List RAMPL::getParameters() const {
  Rcpp::List list;
  const ampl::EntityMap<ampl::Parameter> map = _impl.getParameters();
  ampl::EntityMap<ampl::Parameter>::iterator begin = map.begin();
  ampl::EntityMap<ampl::Parameter>::iterator end = map.end();
  for(ampl::EntityMap<ampl::Parameter>::iterator itr = begin; itr != end; itr++){
    list[itr->name()] = RParameterEntity(*itr);
  }
  return list;
}

/*.. method:: AMPL.setOutputHandler(outputhandler)

  Sets a new output handler.

  :param function outputhandler: The function handling the AMPL output derived from interpreting user commands.
  :return: ``NULL``.
*/
void RAMPL::setOutputHandler(Rcpp::Function outputhandler) {
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
Rcpp::Function RAMPL::getOutputHandler() const {
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
void RAMPL::setErrorHandler(Rcpp::Function errorhandler) {
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
Rcpp::Function RAMPL::getErrorHandler() const {
  if(EHandler != NULL) {
    return EHandler->errorhandler;
  } else {
    throw Rcpp::exception("No error handler defined.");
  }
}

// *** RCPP_MODULE ***
RCPP_MODULE(rampl){
  Rcpp::class_<RAMPL>( "AMPL" )
    .constructor("An AMPL translator")
    .constructor<SEXP>("An AMPL translator")

    .method("toString", &RAMPL::toString)

    .method("cd", &RAMPL::cdStr, "Change the current working directory")
    .method("cd", &RAMPL::cd, "Display the current working directory")

    .method("getOption", &RAMPL::getOption)
    .method("getDblOption", &RAMPL::getDblOption)
    .method("getIntOption", &RAMPL::getIntOption)
    .method("getBoolOption", &RAMPL::getBoolOption)
    .method("setOption", &RAMPL::setOption, "Set an AMPL option to a specified value")

    .method("read", &RAMPL::read, "Interprets the specified file")
    .method("readData", &RAMPL::readData, "Interprets the specified file as an AMPL data file")

    .method("readTable", &RAMPL::readTable)
    .method("writeTable", &RAMPL::writeTable)

    .method("eval", &RAMPL::eval, "Parses AMPL code and evaluates it")
    .method("reset", &RAMPL::reset)
    .method("close", &RAMPL::close)
    .method("isRunning", &RAMPL::isRunning)
    .method("solve", &RAMPL::solve)

    .method("getData", &RAMPL::getData)
    .method("getValue", &RAMPL::getValue)
    .method("setData", &RAMPL::setData)

    .method("getVariable", &RAMPL::getVariable, "Get the variable with the corresponding name")
    .method("getConstraint", &RAMPL::getConstraint, "Get the constraint with the corresponding name")
    .method("getObjective", &RAMPL::getObjective, "Get the objective with the corresponding name")
    .method("getSet", &RAMPL::getSet, "Get the set with the corresponding name")
    .method("getParameter", &RAMPL::getParameter, "Get the parameter with the corresponding name")

    .method("getVariables", &RAMPL::getVariables, "Get all the variables declared")
    .method("getConstraints", &RAMPL::getConstraints, "Get all the constraints declared")
    .method("getObjectives", &RAMPL::getObjectives, "Get all the objectives declared")
    .method("getSets", &RAMPL::getSets, "Get all the sets declared")
    .method("getParameters", &RAMPL::getParameters, "Get all the parameters declared")

    .method("setOutputHandler", &RAMPL::setOutputHandler, "Sets a new output handler")
    .method("getOutputHandler", &RAMPL::getOutputHandler, "Get the current output handler")
    .method("setErrorHandler", &RAMPL::setErrorHandler, "Sets a new error handler")
    .method("getErrorHandler", &RAMPL::getErrorHandler, "Get the current error handler")
    ;
}
